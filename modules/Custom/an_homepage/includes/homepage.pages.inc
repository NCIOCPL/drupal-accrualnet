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
            foreach($contentBlocks as $block){
                $output .= render(node_view(node_load($block['target_id'])));
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



?>
