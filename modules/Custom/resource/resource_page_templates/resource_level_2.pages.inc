<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
function resource_level_2_page($section) {
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
    return $output;
}
