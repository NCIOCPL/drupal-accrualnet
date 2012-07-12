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
$resource_bundle_names = array();

foreach ($an_resource_types as $type => $unused)
{
    $resource_bundle_names[count($resource_bundle_names)] = $type;

}

$GLOBALS['an_lifecycle_fields'] = array(
    // Machine Name => Label
    array(
        'label' => 'Content Summary',
        'description' => 'Provide a summary paragraph for this content to be displayed as a snippet on other pages.',
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
        'description' => 'Provide the content for this page.',
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
    array(
        'label' => 'Child Strategies',
        'field_name' => 'child_strategies',
        'description' => '',
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
        'label' => 'Related Strategy',
        'field_name' => 'related_strategy',
        'description' => '',
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
        'bundles' => $resource_bundle_names,
    ),
    
    array(
        'label' => 'More Resources Link',
        'field_name' => 'more_resources_link',
        'description' => '',
        'type' => 'link_field',
        'cardinality' => 1,
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'lifecycle_strategy',
        ),
    ),
    array(
         'label' => 'Meta Keywords',
        'description' => 'Provide keywords for this page that will be used for tagging for search engines.',
        'field_name' => 'meta_keywords',
        'type' => 'text',
        'cardinality' => 1,
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'lifecycle_strategy',
            'lifecycle_stage',
        ),
    ),
    array(
        'label' => 'Meta Description',
        'description' => 'Provide a description for this page that will be displayed under the title in search results for external search engines like google.',
        'field_name' => 'meta_description',
        'type' => 'text',
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
            'description' => $field['description'],
            'cardinality' => $field['cardinality'],
            'settings' => $field['settings']
        );
    }
    
    // Return the fields
    return $fields;
}


?>
