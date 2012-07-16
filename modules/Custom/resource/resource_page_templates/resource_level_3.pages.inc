<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

module_load_include('inc', 'resource', 'types');
module_load_include('inc', 'an_lifecycle', 'includes/lifecycle.globals');

function DetermineTag($potential) {
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
	global $an_resource_types;
	global $an_stage_strategy;
	print dpm($an_stage_strategy);
	$resources_per_page = 15;

	$postedStage = NULL;
	$postedStrategy = NULL;
	$recognized = array();
	if (isset($_POST['stage'])) {
		print dpm($_POST['stage']);
		$postedStage = $_POST['stage'];
		if ($postedStage == "NULL") {
			$postedStage = NULL;
		}
		/* print dpm($postedStage);
		  if (strstr($postedStage, '&')) {
		  $stages = explode('&', $postedStage);
		  $recognized = array_unique($stages);
		  print dpm($recognized);
		  } else {
		  $recognized = array($postedStage);
		  }
		  unset($_POST['stage']); */
	}
	if (isset($_POST['strategy'])) {
		//print dpm($_POST['strategy']);
		$postedStrategy = $_POST['strategy'];
		if ($postedStrategy == "NULL") {
			$postedStrategy = NULL;
		}
	}

	$vocab = taxonomy_vocabulary_machine_name_load('an_vocabulary_' . $section);
	$vocabName = $vocab->name;
	$tagName = DetermineTag($subsection);
	$tag = array_pop(taxonomy_get_term_by_name($tagName));
	//print dpm($tag);
	if ($tagName == NULL)
		return '';
	$foundStage = NULL;
	$foundStrat = NULL;
	if ($postedStage != NULL) {
		$query = db_select('node', 'n');
		$query = $query->fields('n', array('nid', 'title', 'created', 'type'))
						->condition('n.type', 'lifecycle_stage')
						->condition('n.title', $postedStage);
		//->limit('1');
		$queried_stages = $query->execute()->fetchAllAssoc('nid');

		print dpm($queried_stages);
		if (count($queried_stages) > 0) {
			$foundStage = array_pop($queried_stages);
		}

		if ($postedStrategy != NULL) {

			//$query2->entityCondition('entity_id', $queried_stages[])
			//$query2->fieldCondition('field_child_strategies', 'target_id')
			$query = db_select('node', 'n');
			$query = $query->fields('n', array('nid', 'title', 'created', 'type'))
							->condition('n.type', 'lifecycle_strategy')
							->condition('n.title', $postedStrategy);
			$queried_strats = $query->execute()->fetchAllAssoc('nid');
			print dpm($queried_strats);
			if (count($queried_strats) > 0) {
				$foundStrat = array_pop($queried_strats);
			}
		}
	}

	$query = new EntityFieldQuery();
	// We are looking for a node
	$query->entityCondition('entity_type', 'node');
	//
	$query->entityCondition('bundle', array_keys($an_resource_types));
	//print dpm($vocab);
	$query->fieldCondition('field_tax_' . $section, 'tid', $tag->tid);
	//$query->fieldCondition('field_related_strategy', 'target_id', $tag->tid);
	//$query->propertyCondition('title', $node->title, '=');
	try {
		if ($foundStrat != NULL) {
			print dpm($foundStrat->nid);
			$query->fieldCondition('field_related_strategy', 'target_id', $foundStrat->nid);
		} elseif ($foundStage != NULL) {
			//$query->fieldCondition('field_related_strategy', 'entity_id', $foundStage->nid);
			$query->fieldCondition('field_related_strategy');
		}
	} catch (Exception $e) {
		print dpm($e);
		return '';
	}


	$query->pager($resources_per_page);

	$result = $query->execute();




	//$queried_nodes = $query->execute()->fetchAllAssoc('nid');
	$output = '<div id="resource-level-3">';
	$output .= '<h2>' . $vocabName . '</h2>';
	$output .= '<h3>' . $tagName . '</h3>';

	$output .= '<?php drupal_get_form("ajax_example_simplest"); ?>';

	$output .= '<div id="filter-box">';
	if ($postedStage != NULL || $postedStrategy != NULL) {
		$output .= '<b>Filtered by:</b> ';
		/* foreach ($recognized as $stage) {
		  $filterstage = array_keys($an_stage_strategy);
		  $filterstage = $filterstage[intval($stage)];
		  $output .= $filterstage;
		  $output .= ', ';
		  }
		  if ($postedStrategy != NULL) {
		  $filterstrat = $an_stage_strategy[$filterstage];
		  $filterstrat = array_keys($filterstrat);
		  $filterstrat = $filterstrat[$postedStrategy];
		  } */
		$output .= $postedStage;
		if ($postedStrategy != NULL) {
			$output .= ' -> ' . $postedStrategy;
		}
		$output .= '<br/><br/>';
	}
	$output .= '<form action="" method="post">';

	$output .= '<select name="stage" onChange="this.form.submit()">';
	$output .= '<option value="NULL" selected="selected"></option>';
	foreach (array_keys($an_stage_strategy) as $stage) {
		$output .= '<option value="' . $stage . '" ';
		if ($stage == $postedStage) {
			$output .= 'selected="selected"';
		}
		$output .= ' >' . $stage . '</option>';
	}
	$output .= '</select>';
	/* $i = 0;
	  print dpm($recognized);
	  foreach (array_keys($an_stage_strategy) as $stage) {

	  $output .= '<input type="checkbox" name="stage" value="';
	  if ($postedStage == NULL || !in_array($i, $recognized)) {
	  $output .= $i;
	  if (count($recognized) > 0) {
	  $output .= '&'. implode('&', $recognized);
	  }
	  }
	  $output .= '"';
	  if ($postedStage != NULL && in_array($i, $recognized)) {
	  $output .= ' checked="checked"';
	  }
	  $output .= ' onChange="this.form.submit()" />';
	  $output .= $stage;
	  $output .= '<br/>';
	  $i++;
	  } */
	$output .= '</form>';
	if ($postedStage != NULL) {
		$output .= '<br/>';
		if (array_key_exists($postedStage, $an_stage_strategy)) {
			$output .= '<form action="" method="post">';
			print dpm($postedStage);
			$output .= '<input type="hidden" name="stage" value="' . $postedStage . '"/>';
			$output .= '<select name="strategy" onChange="this.form.submit()">';
			$output .= '<option value="NULL" selected="selected"></option>';
			foreach ($an_stage_strategy[$postedStage] as $strategy) {
				$output .= '<option value="' . $strategy . '" ';
				if ($strategy == $postedStrategy) {
					$output .= 'selected="selected"';
				}
				$output .= ' >' . $strategy . '</option>';
			}
			$output .= '</select>';
			$output .= '</form>';
		}
	}
	$output .= '</div>';

	if (count($result) > 0) {
		$result = $result['node'];
	}
	foreach ($result as $nodeResult) {
		$node = node_load($nodeResult->nid);
		$resultOutput = '<div class="result">';
		$resultOutput .= '<a href="' . url('node/' . $node->nid) . '">';
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
