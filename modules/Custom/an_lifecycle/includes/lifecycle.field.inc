<?php
/* * ***
 * Created By: Doyle
 * Created On:  July 5, 2012
 *
 * Last Updated By: Doyle
 * Last Updated On: July 12, 2012
 * *** */

// Load Resource Types
module_load_include('inc', 'resource', 'includes/types');

//Set array of resource types for entity_reference fields
global $an_resource_types;
//setup array of resource type names
$resource_bundle_names = array();

foreach ($an_resource_types as $type => $unused)
{
    $resource_bundle_names[count($resource_bundle_names)] = $type;

}

/**
 * Setup fields needed/used by the an_lifecycle section of the site. This includes
 * the related_strategy field which is palced on all resource types.
 * Contains information to create the field and the field instance.
 * @global type $GLOBALS['an_lifecycle_fields']
 * @name $an_lifecycle_fields 
 */
$GLOBALS['an_lifecycle_fields'] = array(
    // Machine Name => Label
    array(
        'label' => 'Navigation Label',
        'description' => 'A shortened title of the Lifecycle Strategy used for navigation.',
        'field_name' => 'nav_label',
        'type' => 'text',
        'cardinality' => '1',
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'lifecycle_strategy',
        ),
    ),
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
            'landing_page'
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
        'label' => t('Content Blocks'),
        'field_name' => 'content_blocks',
        'description' => '',
        'type' => 'entityreference',
        'cardinality' => '3',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array('content_block')),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'landing_page'
        ),
    ),
    array(
        'field_name' => 'landing_page_type',
        'label' => t('Landing Page Type'),
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'list_text',
        'settings' => array(
            'allowed_values' => array(
                '0' => t('Protocol Accrual Lifecycle'),
                '1' => t('Literature & Tools'),
                '2' => t('Communities'),
                '3' => t('Education & Training'),
            ),
        ),
        'widget' => array(
            'type' => 'options_select',
        ),
        'bundles' => array(
            'landing_page'
        ),
    )
    
);


/**
 *Returns array of fields containing only information needed to create the field.
 * @global type $an_lifecycle_fields
 * @return string 
 */
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
