<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
module_load_include('inc', 'resource', 'types');
global $an_resource_types;
module_load_include('inc', 'resource', 'citation.field');
global $an_resource_field_citation;
module_load_include('inc', 'resource', 'citation.types');
global $an_resource_citation_fields_A, $an_resource_citation_fields_B, $an_resource_citation_fields_C;
module_load_include('inc', 'resource', 'resource.field');
global $an_resource_field_resource;

module_load_include('inc', 'an_taxonomy', 'resource.globals');
global $an_vocabularies;

module_load_include('module', 'resource');



// Title and Title of Resource
$titleOutput = '<h2>' . $an_resource_types[$type]['name'] . '</h2>';
$titleOutput .= '<h1>'. $title . '</h1>';


// Citation
/*$citationOutput = '<div id="resource-citation">';
switch ($an_resource_types[$type]['citation']) {
    case 'A':
        $citation = $an_resource_citation_fields_A;
        break;
    case 'B':
        $citation = $an_resource_citation_fields_B;
        break;
    case 'C':
        $citation = $an_resource_citation_fields_C;
        break;
}
foreach ($citation as $field_name => $field_properties) {
        $field = array();
        //$field[$field_name] = _resource_citation_change($field_name, $field_properties, $an_resource_field_citation[$field_name]);
    
        foreach ($an_resource_field_citation[$field_name] as $prop_name => $prop_details) {
            $field[$prop_name] = $prop_details; //_resource_citation_change($prop_name, $field_properties, $prop_details);

        }
        foreach ($citation[$field_name] as $diff_prop_name => $diff_prop_details) {
            $field[$diff_prop_name] = $diff_prop_details;
        }
        
            $fieldOutput = '<span class="resource-citation-detail resource-'.$type.'-'.$field_name.'">';
            //$fieldOutput .= $field['label'];
            if ($field['type'] == 'datestamp' && count($variables["field_citation_".$field_name]) > 0) {
                
                $fieldOutput .= date('M d, Y', $variables["field_citation_".$field_name][0]['value']);
                $fieldOutput .= '. ';
            } elseif ($field['cardinality'] > 1 || $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
                foreach ($variables["field_citation_".$field_name] as $field_instance) {
                    $fieldOutput .= $field_instance['value'] . ',';
                }
                $fieldOutput = rtrim($fieldOutput, ',');
                $fieldOutput .= '. ';
            } elseif (count($variables["field_citation_".$field_name])>0) {
                $fieldOutput .= $variables["field_citation_".$field_name][0]['value'];
                $fieldOutput .= '. ';
            }
            $fieldOutput .= '</span>';
            
            $citationOutput .= $fieldOutput;
        }
$citationOutput .= '</div>';
 * 
 */
$node = node_load($nid);
$citationOutput = _resource_output_citation($node);


// Taxonomy (Keywords)
/*$taxonomyOutput = '<div id="resource-taxonomy">';
$taxonomyOutput .= "Keywords: ";
foreach ($an_vocabularies as $vocab) {
    $field_array = ${"field_tax_".$vocab['machine_stem']};
    $vocab_url = '/resources/' . str_replace('an_vocabulary_', '', $vocab['machine_stem']);
    foreach ($field_array as $field_instance) {
        $termName = taxonomy_term_load($field_instance['tid'])->name;
        $old_pattern = array("/[^a-zA-Z0-9]/", "/_+/", "/_$/");
            $new_pattern = array("_", "_", "");
            $term_url = strtolower(preg_replace($old_pattern, $new_pattern, $termName));
            
            $taxonomyOutput .= '<a href="'.$vocab_url.'/'.$term_url.'">';
        $taxonomyOutput .= $termName;
        $taxonomyOutput .= '</a>';
        $taxonomyOutput .= ' &nbsp;&nbsp;';
    }
}

$taxonomyOutput .= '</div>';
 * 
 */

$taxonomyOutput = _resource_output_taxonomy ($node);







// Related Links
$linksOutput = '<div id="resource-links">';
$linksOutput .= '<h3>Links</h3>';
$linksOutput .= '<ul>';
foreach ($field_links as $link) {
    $linksOutput .= '<li>';
    $linksOutput .= '<a href="'.$link['url'].'">';
    $linksOutput .= $link['title'];
    $linksOutput .= '</a>';
    $linksOutput .= '</li>';
}
$linksOutput .= '</ul></div>';


$fieldsToRender = $an_resource_field_resource;
array_pop($fieldsToRender); // This should remove links


$resourceOutput = '<div class="resource-resource">';
foreach($fieldsToRender as $rfield) {
        if (count(${"field_".$rfield["field_name"]}) > 0) {
    $rfieldOutput = '<div id="resource-'.$rfield["field_name"].'">';
    $rfieldOutput .= '<h3>'.$rfield["label"].'</h3>';
    foreach (${"field_".$rfield["field_name"]} as $instance) {
    $rfieldOutput .= $instance['value'];
    }
    $rfieldOutput .= '</div>';
    $resourceOutput .= $rfieldOutput;
    }
}

$resourceOutput .= '</div>';
/*
// Highlights
$highlightsOutput = '<div id="resource-highlights">';
$highlightsOutput .= '<h3>Highlights</h3>';
//$highlightsOutput .= $field_highlights[0]['value'];
$highlightsOutput .= '</div>';


// Description
$descriptionOutput = '<div id="resource-description">';
$descriptionOutput .= '<h3>Description / Usefulness</h3>';
//$descriptionOutput .= $field_description[0]['value'];
$descriptionOutput .= '</div>';


// Details
$detailsOutput = '<div id="resource-details">';
$detailsOutput .= '<h3>Details</h3>';
$detailsOutput .= $field_details[0]['value'];
$detailsOutput .= '</div>';
 * 
 */

// Comments
$commentsOutput = '<div id="resource-comments">';
$commentsOutput .= render($elements['comments']);
$commentsOutput .= '</div>';


// Build the page
print $titleOutput;
print $citationOutput;
print $taxonomyOutput;
print $linksOutput;
/*print $highlightsOutput;
print $descriptionOutput;
print $detailsOutput;
 * 
 */
print $resourceOutput;
print $commentsOutput;

?>
