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
            ->fieldCondition('field_landing_page_type', 'value', 0)
            ->propertyCondition('status', 1);
    $nodes = _an_lifecycle_load_related_nodes($query);
    
    
    $output = '<div id="protocol-landing-page">';
    
    //if we got a node back, pop it off the array. There should only ever be 1 
    //landing page of any type, so we do not care if it has multiple.
    if(!empty($nodes['nodes'])){
        $contentNode = array_pop($nodes['nodes']);
        
        $output .= '<div class="landing-page-image">';
        $output .= '<img src="'.drupal_get_path('theme', 'accrualnet').'/accrualnet-internals/images/avatars/black.png" width="400"/>';   //TODO: implement image field
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
    
            $output .= '<div class="lifecycle-stage">';
             $urlPath = drupal_lookup_path('alias', 'node/'.$entity->nid) != FALSE ?  drupal_lookup_path('alias', 'node/'.$entity->nid) : '/node/'.$entity->nid;           
             $output .= '<h3><a href="/'.$urlPath.'">Stage '.$counter.': '.$stage->title.'</a></h3>';
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
 
    $output .= '</div>';
    return $output;
 
}
