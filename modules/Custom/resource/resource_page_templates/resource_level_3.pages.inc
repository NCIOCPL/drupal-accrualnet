<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


function DetermineTag ($potential) {
    global $an_vocabularies;
    $old_pattern = array("/[^a-zA-Z0-9]/", "/_+/", "/_$/");
    $new_pattern = array("_", "_", "");
    foreach ($an_vocabularies as $vocab) {
        foreach ($vocab['terms'] as $tag) {
            $formatted = strtolower(preg_replace($old_pattern, $new_pattern, $tag));
            if ($formatted == $potential)
                return $tag;
        }
    }
    return NULL;
}

function resource_level_3_page($section, $subsection) {
    $resources_per_page = 15;
    // Now we must query the node list to determine which are conversations
    $query = db_select('node', 'n');
    $query = $query->fields('n', array('nid', 'title', 'created'))
            ->condition('n.status', 1)
            ->condition('n.type', 'resource')
            ->orderBy('n.created', 'DESC') // Newly updated material first
            ->extend('PagerDefault')
            ->limit($resources_per_page)
            ->addTag('node_access');
    $queried_nodes = $query->execute()->fetchAllAssoc('nid');


    // Now we must store the conversations so we can customize their HTML
    $resources = array();
    foreach ($queried_nodes as $result) {
        // We're only going to add a conversation node if it's in a group
       
        $resources[$result->nid] = array(
            'title' => $result->title,
        );

    }

    $vocab = taxonomy_vocabulary_machine_name_load('an_vocabulary_'.$section);
    $vocabName = $vocab->name;
    $tagName = DetermineTag($subsection);
    $tag = array_pop(taxonomy_get_term_by_name($tagName));
    print dpm($tag);
    if ($tagName == NULL) return '';

    
    $output = '<div id="resource-level-2">';
    $output .= '<h2>' .  $vocab->name . '</h2>';
    $output .= $section;
 
   /* foreach (taxonomy_get_tree($vocab->vid) as $tag) {
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
            
            
        $output .= '<div class="resource-level-3-item">';
        $output .= '<h2><a href="/resources/'.$section.'/'.$tag_url.'">'. $tag->name . '</a></h2>';
        $output .= '<hr/>';
        
        
        foreach ($query as $result) {
            $node = node_load($result->entity_id);
            $resultOutput = '<div class="resource-level-2-result">';
            $resultOutput .= '<a href="' . url('node/'.$node->nid) . '">';
            $resultOutput .= $node->title;
            $resultOutput .= '</a>';
            $resultOutput .= _resource_output_citation($node);
            $resultOutput .= _resource_output_taxonomy($node);
            $resultOutput .= '</div>';
            
            $output .= $resultOutput;
        }
        
        $output .= '</div>';
    }
    $output .= '</div>';
    * 
    */
    
    // Now let's build the output for this page
    global $an_resource_types;
    $output = '<div id="allConversations">';
    $output .= '<h2>'.$vocabName.'</h2><h3>'.$tagName.'</h3>';


    $queryString = "SELECT f.entity_id";
        $queryString .= " FROM {field_data_field_tax_".$section."} f";
        $queryString .= " WHERE (";
        foreach ($an_resource_types as $rtype => $rproperties) {
            $queryString .= " f.bundle='".$rtype."' OR ";
        }
        $queryString = trim(rtrim(trim($queryString), 'OR'));
        $queryString .= ") AND f.field_tax_".$section."_tid=" . $tag->tid;
        $queryString .= " LIMIT 2";

        try {
        $query = db_query($queryString);
        } catch (Exception $e) {
           print dpm($e);
        }
        foreach ($query as $result) {
            $node = node_load($result->entity_id);
            $resultOutput = '<div class="resource-level-3-result">';
            $resultOutput .= '<a href="' . url('node/'.$node->nid) . '">';
            $resultOutput .= $node->title;
            $resultOutput .= '</a>';
            $resultOutput .= _resource_output_citation($node);
            $resultOutput .= _resource_output_taxonomy($node);
            $resultOutput .= '</div>';
            
            $output .= $resultOutput;
        }


    // Add the pager
    $output .= theme('pager');

    $output .= '</div>';
    return $output;
}
