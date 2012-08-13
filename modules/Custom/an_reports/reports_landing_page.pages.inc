<?php

/*
 * Created By: Dan Young
 * Created On: 8/1/12
 */

module_load_include('inc', 'resource', 'types');
//add education types global.
module_load_include('inc', 'an_reports', 'includes/reports.globals');

function reports_landing_page() {
	// include report type globals
	global $an_reports_menu;
	
	// build links to reports
	$output = '';
	
	$output .= "<h1>Reports</h1>";
	
	foreach($an_reports_menu as $report => $info)
	{
		$output .= "<div><a href='/admin/reports/accrualnet/$report'>${info['title']}</a></div>";
	}
	
	// done!
	return $output;
}

/*
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
			->fieldCondition('field_landing_page_type', 'value', 'education')
			->propertyCondition('status', 1);
	$nodes = _an_lifecycle_load_related_nodes($query);

	//if we got a node back, pop it off the array. There should only ever be 1
	//landing page of any type, so we do not care if it has multiple.
	if (!empty($nodes['nodes'])) {
		$contentNode = array_pop($nodes['nodes']);
		$output .= _landing_page_output_snippet($contentNode);
	} else {
		$output .= t('Landing page not created yet... please create before launch');
	}

	// find all nodes of the defined types
	foreach ($an_education_menu_vocab as $type) {
		if (!isset($an_resource_types[$type]))
			continue;

		// set up the info and html tag
		$type_info = $an_resource_types[$type];
		$type_tag = str_replace('_', '-', $type);

		// create a block around these nodes and a title
		$output .= "<div class='$type_tag-nodes education-level-2-item'>";

		$query = new EntityFieldQuery();
		$query->entityCondition('entity_type', 'node')
				->entityCondition('bundle', $type)
				->propertyCondition('status', 1)
				->count();
		$count = $query->execute();

		$output .= "<h2 class='$type_tag-title education-title-2'>";
		$output .= "<a href='/education/$type'>${type_info['name']}";
		$output .= "</a>";
		$output .= " <span id='title-results-number' class='education-type-count'>($count)</span>";
		$output .= "</h2>";

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

	if (isset($node->field_content['und'][0]['safe_value'])) {
		$output .= "<div class='landing-page-content'>";
		$output .= filter_xss_admin($node->field_content['und'][0]['value']);
		$output .= '</div>'; // close content div
	}
	$output .= '</div>'; // close text div
	$output .= '</div>'; // close output div
	return $output;
}
*/