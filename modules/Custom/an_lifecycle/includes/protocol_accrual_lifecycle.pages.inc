<?php
/*
 * Created By: Doyle
 * Created On: ?
 * 
 * Last Updated By: Lauren
 * Last Updated On: July 9, 2012
 */

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 * TODO: Move items per page configuration to an admin menu.
 * 
 *  */


function protocol_accrual_lifecycle() {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'landing_page')
            ->fieldCondition('field_landing_page_type', 'value', 'protocol')
            ->propertyCondition('status', 1);
    $nodes = _an_lifecycle_load_related_nodes($query);
    
    
    $output = '<div id="protocol-landing-page">';
    $contentNode = array();
    //if we got a node back, pop it off the array. There should only ever be 1 
    //landing page of any type, so we do not care if it has multiple.
    if(!empty($nodes['nodes'])){
        $contentNode = array_pop($nodes['nodes']);
        
        $output .= '<div class="landing-page-image">';
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
        $output .= '<div class="landing-page-text">';
        $content = field_get_items('node', $contentNode, 'field_content');
        if($content){
            $output .= filter_xss_admin($content[0]['value']);
        }
        $output .= '</div>';
    }
    
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'lifecycle_stage')
            ->propertyCondition('status', 1);
    $nodes = _an_lifecycle_load_related_nodes($query);
    
    $output .= '<div class="lifecycle-stages">';
    if(!empty($nodes['nodes']))
    {
        $counter = 1;
        foreach($nodes['nodes'] as $stage){
    
             $last = $counter == count($nodes['nodes']) ? 'last' : '';
             $output .= '<div class="lifecycle-stage '.$last.'">';
             $urlPath = drupal_lookup_path('alias', 'node/'.$stage->nid) != FALSE ?  drupal_lookup_path('alias', 'node/'.$stage->nid) : '/node/'.$stage->nid;           
             $output .= '<h3><a href="/'.$urlPath.'">STAGE '.$counter.': '.$stage->title.'</a></h3>';
             $contentSummary = field_get_items('node', $stage, 'field_content_summary');
             if($contentSummary){
                 $output.= '<p>';
                 $output .= check_markup($contentSummary[0]['value']);
                 $output.= '</p>';
             }
            $output .= '</div>';
             $counter++;
        }
    }
    $output .= '</div>';
      //if there is a landing page created for this... print out its carousel.
    if(!empty($contentNode)){
        $featuredCarousel = field_get_items('node', $contentNode, 'field_featured_carousel');
        if($featuredCarousel){
            $output .= render(node_view(node_load($featuredCarousel[0]['target_id'])));
        }
    }
 
    $output .= '</div>';
    return $output;
 
}
