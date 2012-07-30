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

function communities_topic ($topic) {
    global $an_communities_field_topic_options;
    if (array_key_exists($topic, $an_communities_field_topic_options)) {
        
        $o = '<div class="communities-topic" id="communities-topic-'.str_replace('_', '-', $topic).'">';
        $o .= '<h1>'.$an_communities_field_topic_options[$topic].'</h1>';
        $term = taxonomy_get_term_by_name($an_communities_field_topic_options[$topic], 'an_vocabulary_topic');
        if (count($term) > 0) {
            $term = array_pop($term);
        }
        if ($term != NULL) {
        if ($term->description) {
            $o .= '<div id="communities-topic-description">'.filter_xss($term->description).'</div>';
        }
        $o .= '<div id="communities-topic-results">';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'conversation')
            //->entityCondition('entity_type', 'og_membership')
            //->propertyCondition('entity_type', 'og_membership')
            //->fieldCondition('field_topic', 'target_id', $term->tid)
            //->fieldCondition('group_audience', 'gid', '0') WORKS
            ->propertyCondition('status', 1)
            ->propertyOrderBy('changed', 'DESC')
            
            ->pager(6);
        
        }
        $convos = _an_lifecycle_load_related_nodes($query, TRUE);
        if (count($convos['nodes']) > 0) {
            $o .= '<h2>Conversations</h2>';
        }
        foreach ($convos['nodes'] as $nid => $convo) {
        $o .= '<div class="conversation-result">';
    $o .= '<div class="conversation-title">';
    $o .= '<a href="' . url('node/' . $convo->nid) . '">';
    //$output .= $node->title;
    $o .= check_plain($convo->title);
    //$output .= filter_xss($node->title);
    $o .= '</a>';
    $o .= '<span class="conversation-last-updated">';
    $o .= 'Last Updated: ';
    $o .= date('M j, Y', $convo->changed);
    $o .= '</span>';
    $o .= '</div>'; // Ends title

    $o .= '<div class="conversation-preview">';
    $bodyContent = $convo->body['und'][0]['value'];
    $bodyTilPeriod = substr($bodyContent, 0, strpos($bodyContent, '.') + 1);
    $o .= $bodyTilPeriod;
    $o .= '</div>';

    $o .= '<div class="conversation-starter">';
    $o .= 'Started by: ';
    $o .= '<a href="' . url('user/' . $node->uid) . '">';
    $o .= user_load($node->uid)->name;
    $o .= '</a>';
    $o .= '</div>';

    $comment = comment_get_thread($convo, COMMENT_MODE_FLAT, 1);
    if ($comment != NULL) {
        $comment = comment_load($comment[0]);
        $commenter = user_load($comment->uid);
        $o .= '<div class="conversation-recent">';
        $o .= '<div class="conversation-recent-text">';
        $o .= 'Recent Activity:';
        $o .= '</div>';
        $o .= '<div class="conversation-recent-comment">';
        /* NOT IMPLEMENTED
          $o .= '<div class="conversation-recent-comment-userpic">';
          $o .= '<img/>';
          $o .= '</div>'; */
        $o .= '<div class="conversation-recent-comment-text">';
        $o .= '<a href="' . url('user/' . $commenter->uid) . '">' . $commenter->name . '</a>';
        $o .= '<br/>';
        $o .= $comment->comment_body['und'][0]['safe_value'];
        $o .= '</div>';
        $o .= '</div>';
        $o .= '</div>';
    }
    $o .= '</div>';
        }
        
        $o .= '</div>';
        $o .= theme('pager');
        
        $o .= '</div>';
        return $o;
    }
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
    foreach ($convos['nodes'] as $nid => $node) {
        if ($x == 4) {
            $o .= '</div><div id="all-conversations-right">';
        }
        $o .= '<div class="all-conversations-result">';
        $o .= '<div class="all-conversations-result-title">';
        $o .= '<a href="'.url('node/'.$nid).'">'. check_plain($node->title) . '</a>';
        $o .= '</div>';
        $o .= '<div class="all-conversations-result-details">';
        $o .= 'Posted by: ';
        $o .= '<a href="'. url('user/' . $node->uid). '">';
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



function communities_of_practice_page () {
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
    foreach ($results['nodes'] as $comm) {
        $o .= '<div class="community-of-practice">';
        $o .= '<div class="community-of-practice-title">';
        $o .= '<a href="' . url('node/'.$comm->vid) .'">';
        $o .= check_plain($comm->title);
        $o .= '</a></div>';
        $o .= '<div class="community-of-practice-desc">';
        $o .= _preview_snippet($comm->body, 4);
        //$o .= drupal_render(field_view_field('node', $comm, 'body', array('label' => 'hidden')));
        $o .= '</div>';
        
        $group = og_get_group('node', $comm->vid);
        if (! in_array($group->gid, array_values($usersGroups))) {
        $o .= '<div class="community-of-practice-link"><span class="community-join-link">';
        $o .= '<a href="'.url('group/node/' . $comm->vid . '/subscribe').'">';
        $o .= 'Join This Community';
        $o .= '</a>';
        $o .= '</span></div>';
        }
        $o .= '</div>';
    }
    $o .= '</div>';
    return $o;
}