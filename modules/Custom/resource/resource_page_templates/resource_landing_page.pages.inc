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
    
 // Now let's build the output for this page
    $output = '<div id="resource-description">';
    $output .= 'AccrualNet supports succesful clinical trial accrual at each stage by providing:';
    $output .= '<br/><br/><ul>';
    $output .= '<li>Linkable access to existing tools and materials</li>';
    $output .= '<li>A searchable, annotated list of published journal articles on clinical trial recruitment</li>';
    $output .= '</ul><br/>';
    $output .= '<div id="resources-list">';
    foreach ($an_resource_menu_vocab as $menu_facet) {
        $vocab = taxonomy_vocabulary_machine_name_load('an_vocabulary_'.$menu_facet);
        $vocab_url = '/resources/' . str_replace('an_vocabulary_', '', $vocab->machine_name);
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
    $output .= '</div>';

    // Add the pager
    $output .= theme('pager');

    $output .= '</div>';
    return $output;
 
}
