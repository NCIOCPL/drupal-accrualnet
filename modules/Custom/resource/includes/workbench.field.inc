<?php
/* * ***
 * Created By: Lauren
 * Created On: June 25, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */

$GLOBALS['an_resource_field_workbench'] = array(
    // Machine Name => Label
    array(
        'label' => 'Assigned Editor',
        'field_name' => 'assigned_editor',
	'type' => 'list_text',
        'cardinality' => 1,
    ),
    array(
        'label' => 'Assigned Writer',
        'field_name' => 'assigned_writer',
	'type' => 'list_text',
        'cardinality' => 1,
    ),
);

function _resource_field_workbench () {
    // Variables
    global $an_resource_field_workbench;
    $fields = array();
    
    // Create the fields
    foreach ($an_resource_field_workbench as $field) {
        $fields[] = array(
            'field_name' => 'field_' . $field['field_name'],
            'type' => $field['type'],
            'cardinality' => $field['cardinality'],
        );
    }
    
    // Return the fields
    return $fields;
}

function _resource_instance_workbench () {
    // Variables
    global $an_resource_field_workbench;
    $instances = array();
    
    // Create the instances
    foreach ($an_resource_field_workbench as $field) {
        $instances[] = array(
            'field_name' => 'field_' . $field['field_name'],
            'label' => $field['label'],
        );
    }
    
    // Return the instances
    return $instances;
}

function _resource_find_workbench ($target) {
    global $an_resource_field_workbench;
    $target = str_replace('field_', '', $target);
    foreach ($an_resource_field_workbench as $field) {
        if ($field['field_name'] == $target) {
            return $true;
        }
    }
    return $false;
}
?>
