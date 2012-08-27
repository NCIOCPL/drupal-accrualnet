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
	global $an_communities_field_topic_descriptions;
	$o = '';
	// Trim the gobblety gook that is appearing on the URL
	if (strpos($topic, '#') > -1) {
		$topic = substr($topic, 0, strpos($topic, '#'));
	}

	if (array_key_exists($topic, $an_communities_field_topic_options)) {

		$long_desc = $an_communities_field_topic_descriptions[$topic];

		$o .= '<div class="communities-topic" id="communities-topic-' . str_replace('_', '-', $topic) . '">';

		// Determine if the topic being passed in exists
		$term = taxonomy_get_term_by_name($an_communities_field_topic_options[$topic], 'an_vocabulary_topic');
		if (count($term) > 0) {
			$term = array_pop($term);
		}

		// Proceed if the topic is recognized
		if ($term != NULL) {

			if ($term->description) {
				$o .= '<div id="communities-topic-description">' . filter_xss($term->description) . '</div>';
			} else if (isset($long_desc)) {
				$o .= '<div id="communities-topic-description">' . filter_xss($long_desc) . '</div>';
			} else {
				$o .= '<br/><br/>';
			}
			$o .= '<div class="start-a-convo">';
                        $o .= '<span class="button">';
                        if(user_is_logged_in())
                            $o .= '<a href="/node/add/conversation" title="Start a Conversation">Start a Conversation</a>';
                        else
                            $o .= '<a href="/user" title="Login">Start a Conversation</a>';
                        $o .='</span></div>  ';

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
			$query->innerJoin('field_data_field_topic', 't', 'n.nid=t.entity_id AND t.field_topic_tid=' . $term->tid);
			$query->innerJoin('node_comment_statistics', 'c', 'n.nid=c.nid');
			$query->condition('n.type', 'conversation')
					->condition('n.status', '1')
					->condition('ogm.gid', 'NULL', 'IS NULL');
			$query->orderBy('c.last_comment_timestamp', 'DESC');
			$query = $query->extend('PagerDefault')->limit($numConvosPerPage);
			$convos = $query->execute()->fetchAllAssoc('nid');


			$convosUnloaded = array_values($convos);
			$numConvos = 0;
			$r = '';
			foreach ($convos as $convoUnloaded) {
				$convo = node_load($convoUnloaded->nid);

				$r .= '<div class="conversation-result';
				if ($convosUnloaded[count($convos) - 1] == $convoUnloaded)
					$r .= ' last-result';
				$r .= '">'; // Start Result

				$r .= _conversation_title_snippet($convo->nid, $convo->title, $convo->last_comment_timestamp);

				$r .= '<div class="conversation-preview">';
				$r .= _preview_snippet($convo->body);
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
	$o = '';
	$numConvosPerPage = 10;
	$query = db_select('node', 'n')->fields('n', array('nid', 'title', 'changed'));
	$query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
	$query->innerJoin('field_data_field_topic', 't', 'n.nid=t.entity_id');
	$query->innerJoin('node_comment_statistics', 'c', 'n.nid=c.nid');
	$query->condition('n.type', 'conversation')
			->condition('n.status', '1')
			->condition('ogm.gid', 'NULL', 'IS NULL');
	$query->orderBy('c.last_comment_timestamp', 'DESC');
	$query = $query->extend('PagerDefault')->limit($numConvosPerPage);
	$convos = $query->execute()->fetchAllAssoc('nid');


	$convosUnloaded = array_values($convos);
	$numConvos = 0;
	$r = '';
	$r .= '<div class="start-a-convo">';
        $r .= '<span class="button">';
        if(user_is_logged_in())
            $r .= '<a href="/node/add/conversation" title="Start a Conversation">Start a Conversation</a>';
        else
            $r .= '<a href="/user" title="Login">Start a Conversation</a>';
        $r .='</span></div>  ';
	foreach ($convos as $convoUnloaded) {
		$convo = node_load($convoUnloaded->nid);

		$r .= '<div class="conversation-result';
		if ($convosUnloaded[count($convos) - 1] == $convoUnloaded)
			$r .= ' last-result';
		$r .= '">'; // Start Result

		$r .= _conversation_title_snippet($convo->nid, $convo->title, $convo->last_comment_timestamp);

		$r .= '<div class="conversation-preview">';
		$r .= _preview_snippet($convo->body);
		$r .= '</div>';

		$r .= _starter_snippet($convo->uid);

		$r .= _get_latest_comment($convo);

		$r .= '</div>'; // End Result

		$numConvos++;
	}
	if ($numConvos > 0) {
		$o .= '<span class="pager top-pager">' . theme('pager') . '</span>';
		$o .= '<div id="conversation-results">';
		$o .= $r;
		$o .= '</div>';
		$o .= '<span class="pager bottom-pager">' . theme('pager') . '</span>';
	} else {
		$o .= 'No conversations found.';
	}



	return $o;
}

function communities_landing_page() {
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'landing_page')
			->fieldCondition('field_landing_page_type', 'value', 'communities')
			->propertyOrderBy('changed', 'DESC')
			->propertyCondition('status', 1);

	$nodes = _an_lifecycle_load_related_nodes($query);

	$output = '<div id="communities-landing-page">';
	//$output .= '<h1>Communities and Conversations</h1>';

	$contentNode = array();
	//if we got a node back, pop it off the array. There should only ever be 1 
	//landing page of any type, so we do not care if it has multiple.
	if (!empty($nodes['nodes'])) {
		$contentNode = array_pop($nodes['nodes']);
		$output .= '<div class="landing-page-header clearfix">';
		$output .= '<div class="landing-page-image">';
		$image = field_get_items('node', $contentNode, 'field_landing_page_image');
		if ($image) {
			$output .= theme('image_style', array(
				'path' => $image[0]['uri'],
				'style_name' => 'large',
					)
			);
		}
		$output .= '</div>';
		$output .= '<div class="landing-page-text">';
		$content = field_get_items('node', $contentNode, 'field_content');
		if ($content) {
			$output .= filter_xss_admin($content[0]['value']);
		}
		$output .= '</div>';

		$output .= '</div>'; //end landing page header
	} else {
		
	}
	//if there is a landing page created for this... print out its carousel.
	if (!empty($contentNode)) {
		$featuredCarousel = field_get_items('node', $contentNode, 'field_featured_carousel');
		if ($featuredCarousel) {
			$output .= render(node_view(node_load($featuredCarousel[0]['target_id'])));
		}
	}
	$output .= '</div>'; // Closes whole page
	return $output;
}

function communities_of_practice_page() {

	//Set message if user tried to join a group that they are pending membership for
	if ($_GET['q'] == "communities/communities_of_practice/pending")
		drupal_set_message("You must be approved to join a Community of Practice. Please check back later.");



	global $user;
	$o = '';
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'landing_page')
			->fieldCondition('field_landing_page_type', 'value', 'communities_of_practice')
			->propertyCondition('status', 1);
	$nodes = _an_lifecycle_load_related_nodes($query);

	if (!empty($nodes['nodes'])) {
		$contentNode = array_pop($nodes['nodes']);
		$image = field_get_items('node', $contentNode, 'field_landing_page_image');

		$o .= '<div class="landing-page-header clearfix">';
		if ($image) {
			$o .= '<div class="landing-page-image">';


			$o .= theme('image_style', array(
				'path' => $image[0]['uri'],
				'style_name' => 'large',
					)
			);
			$o.= '</div>';
			//if there is an image, print out the regular landing page div.
			$o .= '<div class="landing-page-text">';
		} else {
			//if there is no image, print out the no-image div.
			$o .= '<div class="landing-page-text-no-image">';
		}
		$content = field_get_items('node', $contentNode, 'field_content');
		if ($content) {
			$o .= filter_xss_admin($content[0]['value']);
		}
		$o .= '</div>'; //end landing page text
		$o .= '</div>'; //end landing page header
	}

	if (user_is_logged_in()) {
		$o .= '<div class="create-a-community"><span class="button"><a href="/content/create-community">' . t('Create a Community') . '</a></span></div>';
	} else {
		$o .= '<div class="create-a-community"><span class="button"><a href="/user">' . t('Create a Community') . '</a></span></div>';
	}

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'og_membership')
			->propertyCondition('entity_type', 'user')
			->propertyCondition('etid', $user->uid);
	$result = $query->execute();
	$groupmemberships = array();
	if (array_key_exists('og_membership', $result)) {
		$groupmemberships = entity_load('og_membership', array_keys($result['og_membership']));
	}
	$o .= '<div id="communities-of-practice">';
	$o .= '<div id="communities-topic-results">';
	$o .= '<h2>' . t('Communities');

	$o .='</h2></div>';
	$usersGroups = array();

	foreach ($groupmemberships as $throwaway => $ogloaded) {

		$usersGroups[$ogloaded->gid] = $ogloaded->state;
	}

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'community')
			->propertyCondition('status', 1)
			->propertyOrderBy('created', 'ASC')
			->pager(10);
	$results = _an_lifecycle_load_related_nodes($query, TRUE);

	$o .= theme('pager');
	$convosUnloaded = array_values($results['nodes']);
	foreach ($results['nodes'] as $comm) {
		$group = og_get_group('node', $comm->nid);
		$o .= '<div class="community-of-practice clearfix';
		if ($convosUnloaded[count($convosUnloaded) - 1] == $comm)
			$o .= ' last-result';
		$o .= '">';
		$o .= '<div class="community-of-practice-title">';
		if (!in_array($group->gid, array_keys($usersGroups))) {
			if (user_is_logged_in()) {
				$o .='<a href="/group/node/' . $comm->nid . '/subscribe ">';
			} else {
				$o .= '<a href="/user">';
			}
		} else {
			if ($usersGroups[$group->gid] == 2 || $usersGroups[$group->gid] == 3) {
				$o .= '<a href="' . url('communities/communities_of_practice/pending') . '">';
			}
			else
				$o .= '<a href="' . url('node/' . $comm->nid) . '">';
		}
		$o .= check_plain($comm->title);
		$o .= '</a></div>';
		$o .= '<div class="community-of-practice-desc">';
		$o .= _preview_snippet($comm->body);
		//$o .= drupal_render(field_view_field('node', $comm, 'body', array('label' => 'hidden')));
		$o .= '</div>';

		$o .= '<div class="community-of-practice-link">';
		if (!in_array($group->gid, array_keys($usersGroups))) {
			$o .= '<span class="button">';
			if (user_is_logged_in()) {
				$o .= '<a href="/group/node/' . $comm->nid . '/subscribe ">';
			} else {
				$o .= '<a href="/user">';
				//drupal_set_message(t('You must be a registered user in order to join a Community of Practice'));
			}
			$o .= 'Join This Community';
			$o .= '</a>';
			$o .= '</span>';
		} elseif ($usersGroups[$group->gid] == 2 || $usersGroups[$group->gid] == 3) {
			$o .= '<span class="text-grey">';
			$o .= t('Pending Approval');
			$o .='</span>';
		} else {
			$o .= '<span class="button-grey">';
			if (user_is_logged_in()) {
				$o .= '<a href="/group/node/' . $comm->nid . '/unsubscribe ">';
			}

			$o .= 'Leave This Community';
			$o .= '</a>';
			$o .= '</span>';
		}
		$o .= '</div>';
		$userGroupRoles = og_get_user_roles($group->gid, $user->uid);
		if (array_key_exists(3, $userGroupRoles) || in_array('administrator', $user->roles) || in_array('accrualnet_staff', $user->roles)) {
			$o .= '<div class="manage-members">';
			$o .= '<span class="button"><a href="/group/node/' . $group->etid . '/admin/people">Manage Group Members</a></span>';
			$o .= '</div>';
		}

		$o .= '</div>';
	}
	$o .= theme('pager');
	$o .= '</div>';
	return $o;
}