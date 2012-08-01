<?php
/* * ***
 * Created By: Lauren
 * Created On: June 25, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */

$GLOBALS['an_resource_field_resource'] = array(
    // Machine Name => Label
    array(
        'label' => 'Highlights',
        'field_name' => 'highlights',
        'type' => 'text_long',
        'cardinality' => 1,
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
    ),
    array(
        'label' => 'Description',
        'field_name' => 'description',
        'type' => 'text_long',
        'cardinality' => 1,
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
    ),
    array(
        'label' => 'Details',
        'field_name' => 'details',
        'type' => 'text_long',
        'cardinality' => 1,
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
    ),
    array(
        'label' => 'Related Links',
        'field_name' => 'links',
        /*'type' => 'text',
        'cardinality' => FIELD_CARDINALITY_UNLIMITED,
        'widget' => array(
            'type' => 'text_textfield',
        ),
         * 
         */
        'type' => 'link_field',
        'cardinality' => FIELD_CARDINALITY_UNLIMITED,
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
