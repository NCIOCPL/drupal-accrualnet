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

module_load_include('inc', 'an_taxonomy', 'includes/communities.globals');


function communities_topic_page($topic) {
    global $an_communities_field_topic_options;
    
    // Trim the gobblety gook that is appearing on the URL
    if (strpos($topic, '#') > -1) {
        $topic = substr($topic, 0, strpos($topic, '#'));
    }
    
    if (array_key_exists($topic, $an_communities_field_topic_options)) {
        
        $o = '<div class="communities-topic" id="communities-topic-' . str_replace('_', '-', $topic) . '">';

        // Determine if the topic being passed in exists
        $term = taxonomy_get_term_by_name($an_communities_field_topic_options[$topic], 'an_vocabulary_topic');
        if (count($term) > 0) {
            $term = array_pop($term);
        }

        // Proceed if the topic is recognized
        if ($term != NULL) {
            $o .= '<div id="communities-topic-title">';
            $o .= '<h1>' . check_plain($term->name) . '</h1>';
            $o .= '</div>';
            
            if ($term->description) {
                $o .= '<div id="communities-topic-description">' . filter_xss($term->description) . '</div>';
            } else {
                $o .= '<br/><br/>';
            }
            
            $o .= '<div id="communities-topic-results">';
            
            // Get all of the results that are NOT in a group
            // AND have the topic of whatever $term we're looking at
            $queryStr = "SELECT n.nid, n.title, n.changed, "
                . " ogm.gid AS gid"
                . " FROM {node} n "
                . " LEFT JOIN {og_membership} ogm "
                . " ON null OR ogm.etid=n.nid "
                . " INNER JOIN {field_data_field_topic} t "
                . " ON n.nid=t.entity_id AND t.field_topic_tid=" . $term->tid
                . " WHERE n.type='conversation' "
                . " AND n.status='1' "
                . " AND ISNULL(gid) "
                . " ORDER BY nid ASC;";
            
            
            $numConvosPerPage = 10;
            $query = db_select('node', 'n')->fields('n', array('nid', 'title', 'created'));
            $query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
            $query->innerJoin('field_data_field_topic', 't', 'n.nid=t.entity_id AND t.field_topic_tid='.$term->tid);
            $query->condition('n.type', 'conversation')
                    ->condition('n.status', '1')
                    ->condition('ogm.gid', 'NULL', 'IS NULL');
            $query->orderBy('n.created', 'DESC');
            $query = $query->extend('PagerDefault')->limit($numConvosPerPage);
            $convos = $query->execute()->fetchAllAssoc('nid');
            $o .= kprint_r($convos);
            
            $convosUnloaded = array_values($convos);
            $numConvos = 0;
            $r = '';
            foreach ($convos as $convoUnloaded) {
                $convo = node_load($convoUnloaded->nid);
                
                $r .= '<div class="conversation-result';
                if ($convosUnloaded[count($convos) - 1] == $convoUnloaded) $r .= ' last-result';
                $r .= '">'; // Start Result
                
                $r .= _conversation_title_snippet($convo->nid, $convo->title, $convo->changed);
                
                $r .= '<div class="conversation-preview">';
                $r .= _preview_snippet($convo->body, 3);
                $r .= '</div>';
                
                $r .= _starter_snippet($convo->uid);
                
                $r .= _get_latest_comment($convo);
                
                $r .= '</div>'; // End Result
                
                $numConvos++;
            }
            if ($numConvos > 0) {
                $o .= '<h2>Conversations</h2>';
                $o .= '<span class="pager top-pager">' . theme('pager') . '</span>';
                $o .= '<div id="conversation-results">';
                $o .= $r;                
                $o .= '</div>';
                $o .= '<span class="pager bottom-pager">' . theme('pager') . '</span>';
            } else {
                $o .= 'No conversations found.';
            }
            $o .= '</div>';
        }
        
        $o .= '</div>';
        
        return $o;
    } else { 
            // Error handling for IF topic not recongized
            drupal_access_denied();
        }
}

function all_conversations_page() {
    $o = '<div id="all-conversations-page">';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'conversation')
            ->propertyCondition('status', 1)
            ->propertyOrderBy('changed', 'DESC')
            ->pager(8);

    $convos = _an_lifecycle_load_related_nodes($query, TRUE);
    $o .= '<div id="all-conversations-title">';
    $o .= '<span class="all-conversations-pager">';
    $o .= theme('pager');
    $o .= '</span>';
    $o .= '</div>';
    $nids = array_keys($convos);
    $x = 0;
    $o .= '<div id="all-conversations-results">';
    $r = '';
    $convosUnloaded = array_values($convos['nodes']);
    foreach ($convos['nodes'] as $nid => $node) {
        $r .= '<div class="conversation-result';
        if ($convosUnloaded[count($convosUnloaded) - 1] == $node) $o .= ' last-result';
        $r .= '">'; // Start Result
                
                $r .= _conversation_title_snippet($node->nid, $node->title, $node->changed);
                
                $r .= '<div class="conversation-preview">';
                $r .= _preview_snippet($node->body, 3);
                $r .= '</div>';
                
                $r .= _starter_snippet($node->uid);
                
                $r .= _get_latest_comment($node);
                
                $r .= '</div>'; // End Result
    }
    $o .= $r;
    $o .= '</div>';
    $o .= theme('pager');

    $o .= '</div>'; // Closes whole page
    return $o;
}

function communities_landing_page() {
    $o = '<div id="communities-landing-page">';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'landing_page')
            ->fieldCondition('field_landing_page_type', 'value', 'communities')
            ->propertyOrderBy('changed', 'DESC')
            ->propertyCondition('status', 1);

    $result = _an_lifecycle_load_related_nodes($query);


    if (count($result) > 0 && count($result['nodes']) > 0) {
        $landingNode = array_pop($result['nodes']);
        //$o .= kprint_r($landingNode);
        $o .= '<h1>' . $landingNode->title . '</h1>';
        $o .= '<div id="communities-info">';
        $o .= '<div id="communities-pic">';
        $o .= drupal_render(field_view_field('node', $landingNode, 'field_landing_page_image', array('label' => 'hidden')));
        $o .= '</div>';

        $o .= '<div id="communities-description">';
        $o .= drupal_render(field_view_field('node', $landingNode, 'field_content', array('label' => 'hidden')));
        $o .= '</div>'; // Closes Description
        $o .= '</div>'; // Closes Info
    } else {

        $o .= '<h1>Communities and Conversations</h1>';
    }

    $o .= '<div id="all-conversations-box">';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'conversation')
            ->propertyCondition('status', 1)
            ->propertyOrderBy('changed', 'DESC')
            ->pager(8);

    $convos = _an_lifecycle_load_related_nodes($query, TRUE);
    $o .= '<div id="all-conversations-title">';
    $o .= '<span id="all-conversations-title-all">All</span>';
    $o .= '<span id="all-conversations-title-conversations">Conversations</span>';
    $o .= '<span class="all-conversations-pager">';
    $o .= theme('pager');
    $o .= '</span>';
    $o .= '</div>';
    $nids = array_keys($convos);
    $x = 0;
    $o .= '<div id="all-conversations-results">';
    $o .= '<div id="all-conversations-left">';
    $convosUnloaded = array_values($convos['nodes']);
    foreach ($convos['nodes'] as $nid => $node) {
        if ($x == 4) {
            $o .= '</div><div id="all-conversations-right">';
        }
        $o .= '<div class="all-conversations-result';
        $o .= '">';
        $o .= '<div class="all-conversations-result-title">';
        $o .= '<a href="' . url('node/' . $nid) . '">' . check_plain($node->title) . '</a>';
        $o .= '</div>';
        $o .= '<div class="all-conversations-result-details">';
        $o .= 'Posted by: ';
        $o .= '<a href="' . url('user/' . $node->uid) . '">';
        $o .= user_load($node->uid)->name;
        $o .= '</a>';
        $o .= ' on ';
        $o .= date('M j, Y', $node->changed);
        $o .= '</div>';
        $o .= '</div>';
        $x++;
    }
    $o .= '</div></div>';
    $o .= '</div>';

    $o .= '</div>'; // Closes whole page
    return $o;
}

function communities_of_practice_page() {
    global $user;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'og_membership')
            ->propertyCondition('entity_type', 'user')
            ->propertyCondition('etid', $user->uid);
    $result = $query->execute();
    $groupmemberships = entity_load('og_membership', array_keys($result['og_membership']));
    $o = '<div id="communities-of-practice">';
    $usersGroups = array();

    foreach ($groupmemberships as $throwaway => $ogloaded) {
        $usersGroups[] = $ogloaded->gid;
    }

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'community')
            ->propertyCondition('status', 1)
            ->propertyOrderBy('changed', 'DESC')
            ->pager(10);
    $results = _an_lifecycle_load_related_nodes($query, TRUE);
    $o .= theme('pager');
    $convosUnloaded = array_values($results['nodes']);
    foreach ($results['nodes'] as $comm) {
        $o .= '<div class="community-of-practice';
        if ($convosUnloaded[count($convosUnloaded) - 1] == $comm) $o .= ' last-result';
        $o .= '">';
        $o .= '<div class="community-of-practice-title">';
        $o .= '<a href="' . url('node/' . $comm->vid) . '">';
        $o .= check_plain($comm->title);
        $o .= '</a></div>';
        $o .= '<div class="community-of-practice-desc">';
        $o .= _preview_snippet($comm->body, 4);
        //$o .= drupal_render(field_view_field('node', $comm, 'body', array('label' => 'hidden')));
        $o .= '</div>';

        $group = og_get_group('node', $comm->vid);
        if (!in_array($group->gid, array_values($usersGroups))) {
            $o .= '<div class="community-of-practice-link"><span class="community-join-link">';
            $o .= '<a href="/group/node/' . $comm->vid . '/subscribe ">';
            $o .= 'Join This Community';
            $o .= '</a>';
            $o .= '</span></div>';
        }
        $o .= '</div>';
    }
    $o .= theme('pager');
    $o .= '</div>';
    return $o;
}