<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$GLOBALS['an_resource_field_resource'] = array(
    // Machine Name => Label
    array(
        'label' => 'Highlights',
        'field_name' => 'highlights',
        'type' => 'text_long',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Description',
        'field_name' => 'description',
        'type' => 'text_long',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Details',
        'field_name' => 'details',
        'type' => 'text_long',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Related Links',
        'field_name' => 'links',
        'type' => 'text',
        'cardinality' => FIELD_CARDINALITY_UNLIMITED,
        'widget' => array(
            'type' => 'text_textfield',
        ),
    ),
);

function _resource_field_resource () {
    // Variables
    global $an_resource_field_resource;
    $fields = array();
    
    // Create the fields
    foreach ($an_resource_field_resource as $field) {
        $fields[] = array(
            'field_name' => 'field_' . $field['field_name'],
            'type' => $field['type'],
            'cardinality' => $field['cardinality'],
        );
    }
    
    // Return the fields
    return $fields;
}

function _resource_instance_resource () {
    // Variables
    global $an_resource_field_resource;
    $instances = array();
    
    // Create the instances
    foreach ($an_resource_field_resource as $field) {
        $instances[] = array(
            'field_name' => 'field_' . $field['field_name'],
            'label' => $field['label'],
        );
        if (array_key_exists('widget', $field)) { 
            $instances[count($instances)-1]['widget'] = $field['widget'];
        }
    }
    
    // Return the instances
    return $instances;
}

function _resource_find_resource ($target) {
    global $an_resource_field_resource;
    $target = str_replace('field_', '', $target);
    foreach ($an_resource_field_resource as $field) {
        if ($field['field_name'] == $target) {
            return $true;
        }
    }
    return $false;
}
?>
