<?php

module_load_include('module', 'resource');
module_load_include('inc', 'resource', 'types');
module_load_include('inc', 'an_taxonomy', 'includes/resource.globals');


/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function education_level_2_page($section) {
	// grab the resource stylesheet
	$css_path = drupal_get_path('module', 'resource_page_templates');
	$css_path .= "/resources.css";
	drupal_add_css($css_path, array('type' => 'file'));

	global $an_resource_types;

	$output = "";

	if (!isset($an_resource_types[$section]))
		return $output;
	else
		$section_info = $an_resource_types[$section];

	$section_tag = str_replace('_', '-', $section);

	// Now let's build the output for this page
	//$output .= '<div id="resource-description">'; not very descriptive... so modified to resource-landing-page
	$output .= "<div id='$section_tag-landing-page'>";
        //ADDED BY DOYLE 7/30
        $query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'landing_page')
			->fieldCondition('field_landing_page_type', 'value', $section)
			->propertyCondition('status', 1);
	$nodes = _an_lifecycle_load_related_nodes($query);

	 if(!empty($nodes['nodes'])){
            $contentNode = array_pop($nodes['nodes']);
            $output .= '<div class="landing-page-header">';
            $output .= '<div class="landing-page-image">';
            $output .= '<img src="'.drupal_get_path('theme', 'accrualnet').'/accrualnet-internals/images/avatars/male/black.png" width="400"/>';   //TODO: implement image field
            $output .= '</div>';
            $output .= '<div class="landing-page-text">';
            $content = field_get_items('node', $contentNode, 'field_content');
            if($content){
                $output .= filter_xss_admin($content[0]['value']);
            }
            if(!empty($nodes['nodes'])){
            $output .= '</div>'; //end landing page text
            $output .= '</div>'; //end landing page header
            }
        }
        else{
            $output .=  'This landing page is not created... PLEASE SET BEFORE LAUNCH!';
        }
        //END ADDED BY DOYLE
	$output .= "<div class='$section_tag-nodes landing-page-block'>";

	// find all nodes of the materials_staff and materials_patient types
	//in the landing page type field - 2 = Education and Training.
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', $section)
			->propertyCondition('status', 1)
			->pager(10);
	$nodes = _an_lifecycle_load_related_nodes($query, true);

	// get the type count
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', $section)
			->propertyCondition('status', 1)
			->count();
	$count = $query->execute();

	$output .= "<h3 class='education-results'>Results ($count)</h3>";

	$output .= render($nodes['pager']);

	//if we got a node back, pop it off the array. There should only ever be 1
	//landing page of any type, so we do not care if it has multiple.
	foreach ($nodes['nodes'] as $node) {
		$resultOutput = '<div class="education-level-2-result">';
		$resultOutput .= _resource_output_snippet($node, false);
		$resultOutput .= '</div>';

		$output .= $resultOutput;
	}

	$output .= render($nodes['pager']);

	$output .= "</div>";
	$output .= "</div>";

	return $output;
}
