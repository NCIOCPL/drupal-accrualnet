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
			->fieldCondition('field_landing_page_type', 'value', 'education')
			->propertyCondition('status', 1);
	$nodes = _an_lifecycle_load_related_nodes($query);

	//if we got a node back, pop it off the array. There should only ever be 1
	//landing page of any type, so we do not care if it has multiple.
	if (!empty($nodes['nodes'])) {
		$contentNode = array_pop($nodes['nodes']);
		$image = field_get_items('node', $contentNode, 'field_landing_page_image');
                $output .= '<div class="landing-page-header clearfix">';
                $output .= '<div class="landing-page-image">';
                if($image)
                {

                    $output .= theme('image_style',  array(
                                    'path' => $image[0]['uri'],
                                    'style_name' => 'large',         
                                )
                            );
                }
                $output .= '</div>';
                $output .= '<div class="landing-page-text">';
                $content = field_get_items('node', $contentNode, 'field_content');
                if($content){
                    $output .= filter_xss_admin($content[0]['value']);
                }
                $output .= '</div>'; //end landing page text
                $output .= '</div>'; //end landing page header
	} 
        else {
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
				->propertyOrderBy('created', 'DESC')
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
