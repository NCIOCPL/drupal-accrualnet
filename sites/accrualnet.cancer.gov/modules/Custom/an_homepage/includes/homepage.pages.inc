<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


function homepage_display() {
    //get our homepage content item
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'homepage')
             ->propertyOrderBy('created', 'DESC')
            ->propertyCondition('status', 1);
    $nodes = _an_lifecycle_load_related_nodes($query);
    
    $output = '<div id="home">';
    //if we got a node back, pop it off the array. There should only ever be 1 
    //homepage that is public, so we do not care if it has multiple.
    if(!empty($nodes['nodes'])){
        $contentNode = array_pop($nodes['nodes']);
        
        //first thing to do: print out the carousel... add div incase it needs special styling
        $output .= '<div class="homepage-carousel">';
        $featuredCarousel = field_get_items('node', $contentNode, 'field_featured_carousel');
        if($featuredCarousel){
            if (array_key_exists(0, $featuredCarousel) && array_key_exists('target_id', $featuredCarousel[0])) {
                $ftCarousel = $featuredCarousel[0]['target_id'];
                $ftCarousel = node_load($ftCarousel);
                $ftCarousel = node_view($ftCarousel);
                $output .= render($ftCarousel);
            }
        }
        $output .= '</div>';
        
        //Now we want to output the static content that displays in the middle of the
        //page.
        $output .= '<div class="homepage-static-content">';
        $output .= '<div class="homepage-image">';
            $image = field_get_items('node', $contentNode, 'field_landing_page_image');
            if($image)
            {
                $output .= theme('image_style',  array(
                                'path' => $image[0]['uri'],
                                'style_name' => 'large',         
                                'alt' => $image[0]['alt'],
                            )
                        );
            }
            $output .= '</div>';
            $output .= '<div class="homepage-text">';
            $content = field_get_items('node', $contentNode, 'field_content');
            if($content){
                $output .= filter_xss_admin($content[0]['value']);
            }
            $output .= '</div>';
        $output .= '</div>';
        
        
        //Finally, we want to output the additional content blocks displayed at the
        //bottom of the page.
        $output .= '<div class="homepage-content-blocks clearfix">';
        $contentBlocks = field_get_items('node', $contentNode, 'field_content_blocks');
        if($contentBlocks){
            $count = 1;
            foreach($contentBlocks as $block){
                $contentNode = node_load($block['target_id']);
                $last = count($contentBlocks) == $count ? '-last' : '';
                $output .= '<div class="homepage-feature-block-container'.$last.'">';
                switch($contentNode->type){
                    case 'dynamic_content_block':
                        $output .= _homepage_dynamic_content_block($contentNode);
                        break;
                    case 'content_block':
                        $output .= _homepage_content_block($contentNode);
                        break;
                    default:
                        break;
                }
                $output .= '</div>';
                //$output .= render(node_view(node_load($block['target_id'])));
                $count++;
            }
        }
        $output .= '</div>';
        
    }
    else{
        $output .= "Please create a homepage content item";
    }
    
   
    
    $output .= '</div>';
    return $output;
 
}

function _homepage_dynamic_content_block($node) {
    //field_order_by is required
    $order = field_get_items('node', $node, 'field_order_by');
    //field_featured_type is required so it must be here.
    $types = field_get_items('node', $node, 'field_featured_type');
    $link = field_get_items('node', $node, 'field_more_link');
    
    //Redo query buildout.
    
    /*
    //Build out the entityFieldQuery for this content type.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->range(0, 5)
    ->propertyCondition('status', 1);
    //if somehow no types are selected, display all types.
    if($types){
        $query->entityCondition('bundle', array_values($types));
    }
    switch($order[0]['value']){
        case 'alpha':
            $query->propertyOrderBy('title', 'ASC');
            break;
        case 'date_recent':
            $query->propertyOrderBy('created',  'DESC');
            break;
        case 'manual':
            //if manual, dont do anything, we are going to use the order they are inserted in the node.
            break;
        default:
            //this should never be reachable.
            break;
    }


    $featuredContent = _an_lifecycle_load_related_nodes($query, TRUE);
    */
    
    
        $query = '';
        $commentQuery = '';
        $limit = 5;
        
        $output = '';
    
        $output .= '<div class="homepage-feature-title">';
        $output .= '<span class="homepage-feature-header">'.check_plain($node->title).'<span>';
        $output .= '</div>';
        $output .= '<div class="homepage-feature-content">';
	if ($order[0]['value'] != 'manual') {
                $query = db_select('node', 'n')->fields('n', array('nid', 'title', 'created'));
                $query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
		if ($types) {
			$query->condition('n.type', array_values($types), 'IN');
		}
		$query->condition('n.status', '1')
                      ->condition('ogm.gid', 'NULL', 'IS NULL');
                $query->range(0, $limit);
                switch($order[0]['value']){
                    case 'alpha':
                        $query->orderBy('title', 'ASC');
                        break;
                    case 'date_recent':
                        $query->orderBy('created',  'DESC');
                        break;
                    case 'manual':
                        //if manual, dont do anything, we are going to use the order they are inserted in the node.
                        break;
                    default:
                        //this should never be reachable.
                        break;
                }
		

		if ($order[0]['value'] != 'aplha')
                {
                    //This is not very efficient, but it gets the job done (Doyle)
                    foreach($types as $type){
                        if($type['value'] == 'conversation'){
                            $commentQuery = db_select('comment', 'c')->fields('c', array('nid', 'cid', 'subject', 'created'));
                            $commentQuery->leftJoin('node', 'n', 'c.nid=n.nid');
                            $commentQuery->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
                            $commentQuery->condition('c.status', '1')
                                        ->condition('ogm.gid', 'NULL', 'IS NULL');
                            $commentQuery->condition('n.type', 'conversation');
                            $commentQuery->range(0,$limit);    
                            switch($order[0]['value']){
                                    case 'alpha':
                                        $commentQuery->orderBy('n.title', 'ASC');
                                        break;
                                    case 'date_recent':
                                        $commentQuery->orderBy('created',  'DESC');
                                        break;
                                    case 'manual':
                                        //if manual, dont do anything, we are going to use the order they are inserted in the node.
                                        break;
                                    default:
                                        //this should never be reachable.
                                        break;
                                }
                        }
                    }
                }

		$content = $query->execute();
                $content = $content->fetchAllAssoc('nid');
                if($commentQuery){
                    $content = array_merge($content, $commentQuery->execute()->fetchAllAssoc('cid'));
                    
                }
                usort($content, 'feature_sort');
                $content = array_slice($content, 0, $limit);
                //$test = array_multisort($content);
                //$featuredContent = entity_load('node', array_keys($content));
		

		
		foreach($content as $nid => $values){
                    if(array_key_exists('title', $values)){
                        $item = node_load($values->nid);
                    }
                    else{
                        $item = comment_load($values->cid);
                        
                    }
			
			$output .= _homepage_featured_content_display($item);
			
		}
		
	}
    
   /*
    foreach($featuredContent['nodes'] as $item){
        $color = $item->type == 'conversation' ? 'Orange' : 'Blue';
        $output .= '<div class="homepage-feature-content-item">';
        $urlPath = drupal_lookup_path('alias', 'node/'.$item->nid); 
        $output .= '<div class="homepage-node-created '.$color.'">';
        $output .= format_date(check_plain($item->created), 'custom', 'm/d/y');
        $output .= '</div>';
        $output .= '<div class="homepage-node-title">';
        
        $output .= '<a href="'.$urlPath.'" title="'.check_plain($item->title).'">';
        $output .= check_plain($item->title);
        $output .= '</a>';
        if($item->type == 'conversation'){
            $output .= '<div class="node-posted-by">';
            $output .= 'Posted By: '. check_plain($item->name) ;
            $output .= '</div>';
        }
        $output .= '</div>';
        $output .= '</div>';
    }
    * 
    */
    if($link){
        $output .= '<div class="feature-link">';
        $output .= '<span class="button"><a href="/'.$link[0]['url'].'" title="'.$link[0]['title'].'">'.$link[0]['title'].'</a></span>';
        $output .= '</div>';
    }
    $output .= '</div>';
    return $output;
}

function _homepage_content_block($node) {
    $body = field_get_items('node', $node, 'field_content');
    $output = '';
    
    $output .= '<div class="homepage-feature-title">';
    $output .= '<span class="homepage-feature-header">'.check_plain($node->title).'<span>';
    $output .= '</div>';
    $output .= '<div class="homepage-feature-content">';
    if($body){
        $output .= '<div class="homepage-feature-content-item">';

        $output .= '<div class="homepage-node-output">';

        $output .= $body[0]['value'];
        $output .= '</div>';
        $output .= '</div>';
    }
    
    $output .= '</div>';
    return $output;
}

?>
