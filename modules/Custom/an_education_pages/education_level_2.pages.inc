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

	// find all nodes of the materials_staff and materials_patient types
	//in the landing page type field - 2 = Education and Training.
	/* $query = new EntityFieldQuery();
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
	  } */

	$output .= "<div class='$section_tag-nodes level-2-block'>";

	// find all nodes of the materials_staff and materials_patient types
	//in the landing page type field - 2 = Education and Training.
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', $section)
			->propertyCondition('status', 1)
			->pager(10);
	$nodes = _an_lifecycle_load_related_nodes($query, true);

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

	/* $output .= '<div id="resource-level-2">';
	  $output .= '<h2>' .  $vocab->name . '</h2>';

	  foreach (taxonomy_get_tree($vocab->vid) as $tag) {
	  $queryString = "SELECT f.entity_id";
	  $queryString .= " FROM {field_data_field_tax_".$section."} f";
	  $queryString .= " WHERE (";
	  foreach ($an_resource_types as $rtype => $rproperties) {
	  $queryString .= " f.bundle='".$rtype."' OR ";
	  }
	  $queryString = trim(rtrim(trim($queryString), 'OR'));
	  $queryString .= ") AND f.field_tax_".$section."_tid=" . $tag->tid;
	  $queryString .= " LIMIT 2";

	  $query = db_query($queryString);



	  $old_pattern = array("/[^a-zA-Z0-9]/", "/_+/", "/_$/");
	  $new_pattern = array("_", "_", "");
	  $tag_url = strtolower(preg_replace($old_pattern, $new_pattern, $tag->name));


	  $output .= '<div class="resource-level-2-item">';
	  $output .= '<h2><a href="/literature/'.$section.'/'.$tag_url.'">'. $tag->name . '</a></h2>';
	  $output .= '<hr/>';


	  foreach ($query as $result) {
	  $node = node_load($result->entity_id);
	  $resultOutput = '<div class="resource-level-2-result">';
	  $resultOutput .= _resource_output_snippet($node);
	  $resultOutput .= '</div>';

	  $output .= $resultOutput;
	  }

	  $output .= '</div>';
	  }
	  $output .= '</div>'; */
	return $output;
}
