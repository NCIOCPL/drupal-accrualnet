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
    $tag = taxonomy_get_term_by_name($tagName);
    print dpm($tag);
    if ($tagName == NULL) return '';
    
    // Now let's build the output for this page
    $output = '<div id="allConversations">';
    $output .= '<h2>'.$vocabName.'</h2><h3>'.$tagName.'</h3>';
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
    return $output;
}
