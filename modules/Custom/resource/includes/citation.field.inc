<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$GLOBALS['an_resource_field_citation'] = array(
    // Machine Name => Label
    array(
        'label' => 'Author(s)',
        'field_name' => 'author',
        'type' => 'text',
        'cardinality' => FIELD_CARDINALITY_UNLIMITED,
    ),
    array(
        'label' => 'Resource Name',
        'field_name' => 'name',
        'type' => 'text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Date',
        'field_name' => 'date',
        'type' => 'datestamp',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Volume',
        'field_name' => 'volume',
        'type' => 'text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Issue Number',
        'field_name' => 'issue',
        'type' => 'text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Page(s)',
        'field_name' => 'pages',
        'type' => 'text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation EPub Date',
        'field_name' => 'date_epub',
        'type' => 'datestamp',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Year',
        'field_name' => 'year',
        'type' => 'text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Citation Organization',
        'field_name' => 'organization',
        'type' => 'text',
        'cardinality' => 2,
    ),
);

function _resource_field_citation () {
    // Variables
    global $an_resource_field_citation;
    $fields = array();
    
    // Create the fields
    foreach ($an_resource_field_citation as $field) {
        $fields[] = array(
            'field_name' => 'field_citation_' . $field['field_name'],
            'type' => $field['type'],
            'cardinality' => $field['cardinality'],
        );
    }
    
    // Return the fields
    return $fields;
}

function _resource_instance_citation () {
    // Variables
    global $an_resource_field_citation;
    $instances = array();
    
    // Create the instances
    foreach ($an_resource_field_citation as $field) {
        $instances[] = array(
            'field_name' => 'field_citation_' . $field['field_name'],
            'label' => $field['label'],
        );
    }
    
    // Return the instances
    return $instances;
}

function _resource_find_citation ($target) {
    global $an_resource_field_citation;
    $target = str_replace('field_citation_', '', $target);
    foreach ($an_resource_field_citation as $field) {
        if ($field['field_name'] == $target) {
            return $true;
        }
    }
    return $false;
}
?>
