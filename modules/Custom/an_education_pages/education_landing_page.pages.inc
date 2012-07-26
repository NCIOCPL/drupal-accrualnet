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

module_load_include('inc', 'resource', 'types');
//add education types global.
module_load_include('inc', 'an_education_pages', 'includes/education.globals');

function education_landing_page() {
	$output = "";

	// grab the resource stylesheet
	$css_path = drupal_get_path('module', 'resource_page_templates');
	$css_path .= "/resources.css";
	drupal_add_css($css_path, array('type' => 'file'));

	global $an_resource_types, $an_education_menu_vocab;

	// Now let's build the output for this page
	$output .= '<div id="education-landing-page">';

	// find all nodes of the materials_staff and materials_patient types
	//in the landing page type field - 2 = Education and Training.
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'landing_page')
			->fieldCondition('field_landing_page_type', 'value', 3)
			->propertyCondition('status', 1);
	$nodes = _an_lifecycle_load_related_nodes($query);

	//if we got a node back, pop it off the array. There should only ever be 1
	//landing page of any type, so we do not care if it has multiple.
	if (!empty($nodes['nodes'])) {
		$contentNode = array_pop($nodes['nodes']);
		$output .= _landing_page_output_snippet($contentNode);
	}

	// find all nodes of the defined types
	foreach ($an_education_menu_vocab as $type) {
		if (!isset($an_resource_types[$type]))
			continue;

		// set up the info and html tag
		$type_info = $an_resource_types[$type];
		$type_tag = str_replace('_', '-', $type);

		// create a block around these nodes and a title
		$output .= "<div class='$type_tag-nodes landing-page-block'>";

		$query = new EntityFieldQuery();
		$query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', $type)
				->propertyCondition('status', 1)
				->count();
		$count = $query->execute();

		$output .= "<h3 class='$type_tag-title education-text'>${type_info['name']}";
		$output .= " <span class='education-type-count'>($count)</span>";
		$output .= "</h3>";

		// find the related nodes
		$query = new EntityFieldQuery();
		$query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', $type)
				->propertyCondition('status', 1)
				->range(0, 3);
		$nodes = _an_lifecycle_load_related_nodes($query);

		// print the snippet for each node
		foreach ($nodes['nodes'] as $node) {
			$resultOutput = '<div class="education-level-2-result">';
			$resultOutput .= _resource_output_snippet($node, false);
			$resultOutput .= '</div>';

			$output .= $resultOutput;
		}

		// build the 'see more...' button
		$output .= "<div class='form-actions form-wrapper'>";
		$output .= "<input type='button' value='See all ${type_info['name']}' onClick='parent.location=\"education/$type\"'>";
		$output .= "</div>";
		$output .= "</div>";
	}

	$output .= '</div>'; //end div resource landing page
	return $output;
}

function _landing_page_output_snippet($node) {
	$image = '';
	try {
		//$theme_path = drupal_get_path('theme', 'accrualnet');
		if (isset($node->field_landing_page_image['und'][0]['uri'])) {
			$image = check_plain($node->field_landing_page_image['und'][0]['uri']);
			$image = file_create_url($image);
		}

		$image = "<img src='$image'>";
	} catch (Exception $e) {
		$image = $e->getMessage();
	}

	$output = '<div class="landing-page-output">';
	$output .= '<div class="landing-page-output-image">';
	$output .= $image;
	$output .= '</div>'; // close image div
	$output .= '<div class="landing-page-text">';
	/*$output .= '<div class="landing-page-output-title">';
	$output .= check_plain($node->title);
	$output .= '</div>';*/ // close title div

	if (isset($node->field_content['und'][0]['safe_value'])) {
		$output .= "<div class='landing-page-content'>";
		$output .= filter_xss_admin($node->field_content['und'][0]['value']);
		$output .= '</div>'; // close content div
	}
	$output .= '</div>'; // close text div
	$output .= '</div>'; // close output div
	return $output;
}