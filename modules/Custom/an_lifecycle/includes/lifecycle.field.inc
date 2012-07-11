<?php
/* * ***
 * Created By: Lauren
 * Created On: June 25, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */

// Resource Types
module_load_include('inc', 'resource', 'includes/types');
global $an_resource_types;
//setup array of resource type names
$bundle_name = array();

foreach ($an_resource_types as $type => $properties)
{
    $bundle_name[count($bundle_name)] = $type;

}

$GLOBALS['an_lifecycle_fields'] = array(
    // Machine Name => Label
    array(
        'label' => 'Child Strategies',
        'field_name' => 'child_strategies',
        'type' => 'entityreference',
        'cardinality' => '-1',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array('lifecycle_strategy')),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'lifecycle_stage',
        ),
    ),
    array(
        'label' => 'Related Resources',
        'field_name' => 'related_resources',
        'type' => 'entityreference',
        'cardinality' => '-1',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => $bundle_name),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'lifecycle_strategy',
        ),
    ),
    array(
        'label' => 'Content Summary',
        'field_name' => 'content_summary',
        'type' => 'text_long',
        'cardinality' => 1,
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'lifecycle_strategy',
            'lifecycle_stage',
        ),
    ),
    array(
        'label' => 'Content',
        'field_name' => 'content',
        'type' => 'text_long',
        'cardinality' => 1,
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'lifecycle_strategy',
            'lifecycle_stage',
        ),
    ),
    
);

function _an_lifecycle_field_lifecycle() {
    // Variables
    global $an_lifecycle_fields;
    $fields = array();
    
    // Create the fields
    foreach ($an_lifecycle_fields as $field) {
        $fields[] = array(
            'field_name' => 'field_' . $field['field_name'],
            'type' => $field['type'],
            'cardinality' => $field['cardinality'],
            'settings' => $field['settings']
        );
    }
    
    // Return the fields
    return $fields;
}


?>
