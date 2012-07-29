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
            $output .= render(node_view(node_load($featuredCarousel[0]['target_id'])));
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
        $output .= '<div class="homepage-content-blocks">';
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
    

    //Build out the entityFieldQuery for this content type.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', array_values($types))
    ->range(0, 5)
    ->propertyCondition('status', 1);
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
    
    $output = '';
    
    $output .= '<div class="homepage-feature-title">';
    $output .= '<span class="homepage-feature-header">'.check_plain($node->title).'<span>';
    $output .= '</div>';
    $output .= '<div class="homepage-feature-content">';
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
