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

module_load_include('inc', 'an_taxonomy', 'includes/resources.globals');

function resource_landing_page() {
    global $an_vocabularies, $an_resource_menu_vocab;
    
    
    
    /******Added by Doyle 7/24*******/
    
    $output = "";
    
    // Now let's build the output for this page
    //$output .= '<div id="resource-description">'; not very descriptive... so modified to resource-landing-page
    $output .= '<div id="literature-landing-page">';
    //in the landing page type field - 1 = Literature and Tools.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'landing_page')
            ->fieldCondition('field_landing_page_type', 'value', 'literature')
            ->propertyCondition('status', 1);
    $nodes = _an_lifecycle_load_related_nodes($query); 
    
    
    //if we got a node back, pop it off the array. There should only ever be 1 
    //landing page of any type, so we do not care if it has multiple.
    if(!empty($nodes['nodes'])){
        $contentNode = array_pop($nodes['nodes']);
        $output .= '<div class="landing-page-header">';
        $output .= '<div class="landing-page-image">';
        $output .= '<img src="'.drupal_get_path('theme', 'accrualnet').'/accrualnet-internals/images/avatars/male/black.png" width="400"/>';   //TODO: implement image field
        $output .= '</div>';
        $output .= '<div class="landing-page-text">';
        $content = field_get_items('node', $contentNode, 'field_content');
        if($content){
            $output .= filter_xss_admin($content[0]['value']);
        }
        $output .= '</div>'; //end landing page text
        $output .= '</div>'; //end landing page header
    }
    /*****End Added by Doyle*********/
  //  $output .= 'AccrualNet supports succesful clinical trial accrual at each stage by providing:';
  //  $output .= '<br/><br/><ul>';
  //  $output .= '<li>Linkable access to existing tools and materials</li>';
  //  $output .= '<li>A searchable, annotated list of published journal articles on clinical trial recruitment</li>';
  //  $output .= '</ul><br/>';
    $output .= '<div id="resources-list">';
    foreach ($an_resource_menu_vocab as $menu_facet) {
        $vocab = taxonomy_vocabulary_machine_name_load('an_vocabulary_'.$menu_facet);
        $vocab_url = '/literature/' . str_replace('an_vocabulary_', '', $vocab->machine_name);
        $taxonomy = taxonomy_get_tree($vocab->vid);

        $output .= '<div class="resource-issue">';
        $output .= '<h2><a href="'.$vocab_url.'">'.$vocab->name.'</a></h2>';
        $output .= 'What are provider-related issues? Donec at enim eget risus adipiscing euismod vitae eu
nisl. Nullam tempus pretium purus ac auctor. Donec non nisi vel nisi tincidunt imperdiet
dictum vitae ante.';
        $output .= '<br/><br/>';
        $termOutput = '';
        foreach ($taxonomy as $term) {
            $old_pattern = array("/[^a-zA-Z0-9]/", "/_+/", "/_$/");
            $new_pattern = array("_", "_", "");
            $term_url = strtolower(preg_replace($old_pattern, $new_pattern, $term->name));
            
            //$termOutput .= '<a href="/taxonomy/term/'.$term->tid.'">'.$term->name . '</a> | ';
            $termOutput .= '<a href="' . $vocab_url . '/' . $term_url . '">'.$term->name . '</a> | ';
        }
        $output .= trim(rtrim(trim($termOutput), '|')); // Removes the last |
        $output .= '</div>';
    }
    $output .= '</div>'; //end div resource list

    // Add the pager
    $output .= theme('pager');

    $output .= '</div>'; //end div resource landing page
    return $output;
 
}
