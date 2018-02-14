<?php

/* Created By: Lauren
 * Created On: June 8, 2012
 * Last Updated By: Lauren
 * Last Updated On: June 11, 2012
 * 
 * Please test out in a template file before copying here to avoid blowing up 
 * the module.
 */

/**
 * Menu callback to provide a list of all conversations
 */
function all_conversations_page() {
    // First thing we do is customize the page for the user
    global $user;
    // Next we get our user's groups
    $usersGroups = og_get_entity_groups('user');

    // We also must pick how many conversations there will be per page
    $conversations_per_page = 10;

    // Figuring out which group(s) a conversation is in must be done separately.
    // An effort was made to do the query together, but it messes with the pager
    // due to the possibility of multiple entries in the og_membership database.
    $gidQuery = db_select('og_membership', 'g');
    $gidQuery = $gidQuery->fields('g', array('etid', 'gid'))
            ->condition('g.entity_type', 'node');
    $gidExecute = $gidQuery->execute()->fetchAllAssoc('etid');

    // After querying, we must collect all of the groups for each node (etid).
    // We don't actually know if these are conversation nodes yet, but we sort that 
    // out later.
    $groups_by_convos = array();
    foreach ($gidExecute as $result) {
        // At this time, we are only taking the first group as the result
        // We have chosen not to support multiple group membership functionalities
        if (!in_array($result->etid, $groups_by_convos)) {
            $groups_by_convos[$result->etid] = $result->gid;
        }
    }


    // Now we must query the node list to determine which are conversations
    $query = db_select('node', 'n');
    $query->join('node_comment_statistics', 'c', 'n.nid = c.nid'); // We must join with this table to get the last updated date
    $query = $query->fields('n', array('nid', 'title', 'created'))
            ->fields('c', array('last_comment_timestamp')) // This defaults to when the node was last updated/created if no comments (I think)
            ->condition('n.status', 1)
            ->condition('n.type', 'conversation')
            ->orderBy('c.last_comment_timestamp', 'DESC') // Newly updated material first
            ->extend('PagerDefault')
            ->limit($conversations_per_page)
            ->addTag('node_access');
    $queried_nodes = $query->execute()->fetchAllAssoc('nid');


    // Now we must store the conversations so we can customize their HTML
    $conversations = array();
    foreach ($queried_nodes as $result) {
        // We're only going to add a conversation node if it's in a group
        if (array_key_exists($result->nid, $groups_by_convos)) {
            $conversations[$result->nid] = array(
                'title' => $result->title,
                'gid' => $groups_by_convos[$result->nid] // Pull the group ID from the other array
            );
        }
    }

    // Now let's build the output for this page
    $output = '<div id="allConversations">';
    $output .= '<ul>';
    foreach ($conversations as $resultNid => $result) {
        // We must check if the 'title' exists, otherwise, it was not a conversation node
        if (array_key_exists('title', $result)) {
            $output .= '<li class="conversation"><span class="conversationText">';
            if (in_array($result['gid'], $usersGroups)) {
                $output .= l($result['title'], "node/$resultNid");
            } else {
                $output .= $result['title'];
                $output .= '</span><span class="joinButton">';
                $output .= '<a href="/group/node/' . $result['gid'] . '/subscribe">Join</a>';
            }
            $output .= "</span></li>";
        }
    }
    $output .= '</ul>';

    // Add the pager
    $output .= theme('pager');

    $output .= '</div>';
    return $output;
}

