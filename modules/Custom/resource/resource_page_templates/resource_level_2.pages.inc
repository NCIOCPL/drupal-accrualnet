<?php

module_load_include('inc', 'resource', 'types');
module_load_include('inc', 'an_taxonomy', 'includes/resource.globals');


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
function resource_level_2_page($section) {
    global $an_resource_types;
    global $an_vocabularies;
    /*
     $resources_per_page = 15;
    // Now we must query the node list to determine which are conversations
    $query = db_select('node', 'n');
    $query = $query->fields('n', array('nid', 'title', 'created', 'type'))
            ->condition('n.status', 1)
            ->condition(
            //->db_or()
              //  ->condition('n.type', 'materials_patient')
                
                db_or()->condition('n.type', array_keys($an_resource_types))
                    )
            ->orderBy('n.created', 'DESC') // Newly updated material first
            ->extend('PagerDefault')
            ->limit($resources_per_page)
            ->addTag('node_access');
    $queried_nodes = array(); //$query->execute()->fetchAllAssoc('nid');



    // Now we must store the conversations so we can customize their HTML
    $resources = array();
    foreach ($queried_nodes as $result) {
        // We're only going to add a conversation node if it's in a group
       
        $resources[$result->nid] = array(
            'title' => $result->title,
        );

    }
    


    // Now let's build the output for this page
    $output = '<div id="allConversations">';
    $output .= '<h2>'.$section.'</h2>';
    $output .= '<ul>';
    foreach ($resources as $resultNid => $result) {
        // We must check if the 'title' exists, otherwise, it was not a conversation node
        if (array_key_exists('title', $result)) {
            $output .= '<li class="resource"><span class="resourceText">';            
                $output .= $result['title'];
            $output .= "</span></li>";
        }
    }
    $output .= '</ul>';

    // Add the pager
    $output .= theme('pager');

    $output .= '</div>';
     * 
     */


    $vocab = taxonomy_vocabulary_machine_name_load('an_vocabulary_'.$section);
    $output = '<div id="resource-level-2">';
    $output .= '<h2>' .  $vocab->name . '</h2>';
 
    foreach (taxonomy_get_tree($vocab->vid) as $tag) {
        $queryString = "SELECT f.entity_id";
        $queryString .= " FROM {field_data_field_tax_".$section."} f";
        $queryString .= " WHERE (";
        foreach ($an_resource_types as $rtype => $rproperties) {
            $queryString .= " f.bundle='".$rtype."' OR ";
        }
        $queryString = trim(rtrim(trim($queryString), 'OR'));
        $queryString .= ") AND f.field_tax_".$section."_tid=" . $tag->tid;
        $queryString .= " LIMIT 2";
      
        $query = db_query($queryString);
        

        
        $old_pattern = array("/[^a-zA-Z0-9]/", "/_+/", "/_$/");
            $new_pattern = array("_", "_", "");
            $tag_url = strtolower(preg_replace($old_pattern, $new_pattern, $tag->name));
            
            
        $output .= '<div class="resource-level-2-item">';
        $output .= '<h2><a href="/resources/'.$section.'/'.$tag_url.'">'. $tag->name . '</a></h2>';
        $output .= '<hr/>';
        
        
        foreach ($query as $result) {
            $node = node_load($result->entity_id);
            $resultOutput = '<div class="resource-level-2-result">';
            $resultOutput .= '<a href="' . url('node/'.$node->nid) . '">';
            $resultOutput .= $node->title;
            $resultOutput .= '</a>';
            $resultOutput .= '</div>';
            
            $output .= $resultOutput;
        }
        
        $output .= '</div>';
    }
    $output .= '</div>';
    return $output;
}
