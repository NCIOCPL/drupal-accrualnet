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
        'field_name' => 'strategy_icon',
        'label' => t('Strategy Icon'),
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => 'This icon is what shows up on the left of a strategy on a Stage page.',
        'type' => 'image',
        'settings' => array(
            'uri_scheme' => 'public',
            'default_image' => FALSE,
            'user_register_form' => FALSE, // default
            'file_directory' => 'images', // default ''
            'file_extensions' => 'png gif jpg jpeg', // default
            'max_filesize' => '', // default
            'max_resolution' => '', // default
            'min_resolution' => '',  // default,
            'alt_field' => FALSE, // default
            'title_field' => FALSE, // default
        ),
        'widget' => array(
            'type' => 'image_image',
            'settings' => array(
            'progress_indicator' => 'bar', // default is 'throbber'
            'preview_image_style' => 'thumbnail', // default
            ),
        ),
        'bundles' => array(
            'lifecycle_strategy'
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
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
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
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
        'bundles' => array(
            'lifecycle_stage',
            'landing_page'
        ),
    ),
    array(
        'label' => 'Activities',
        'description' => 'Provide the activities to be printed out on a strategy page.',
        'field_name' => 'activities',
        'type' => 'text_long',
        'cardinality' => '5',
        'entity_type' => 'node',
        'settings' => array(
            'text_processing' => '1',
        ),
        'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
        'bundles' => array(
            'lifecycle_strategy',
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
    /*   
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
    ),*/
    array(
        'field_name' => 'landing_page_type',
        'label' => t('Landing Page Type'),
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'list_text',
        'settings' => array(
            'allowed_values' => array(
                'protocol' => t('Protocol Accrual Lifecycle'),
                'literature' => t('Literature & Tools'),
                'patient_related' => t('Patient Related Issues'),
                'provider_related' => t('Provider Related Issues'),
                'system_and_regulatory' => t('System and Regulatory Issues'),
                'study' => t('Study Issues'),
                'ethical' => t('Ethical Issues'),
                'communities' => t('Communities'),
                'education' => t('Education & Training'),
                'materials_staff' => t('Staff Education Materials'),
                'materials_patient' => t('Patient Education Materials')
            ),
        ),
        'widget' => array(
            'type' => 'options_select',
        ),
        'bundles' => array(
            'landing_page'
        ),
    ),
    array(
        'field_name' => 'landing_page_image',
        'label' => t('Landing Page Image'),
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'image',
        'settings' => array(
            'uri_scheme' => 'public',
            'default_image' => FALSE,
            'user_register_form' => FALSE, // default
            'file_directory' => 'images', // default ''
            'file_extensions' => 'png gif jpg jpeg', // default
            'max_filesize' => '', // default
            'max_resolution' => '', // default
            'min_resolution' => '',  // default,
            'alt_field' => FALSE, // default
            'title_field' => FALSE, // default
        ),
        'widget' => array(
            'type' => 'image_image',
            'settings' => array(
            'progress_indicator' => 'bar', // default is 'throbber'
            'preview_image_style' => 'thumbnail', // default
            ),
        ),
        'bundles' => array(
            'landing_page'
        ),
    ),
    array(
        'field_name' => 'stage_image',
        'label' => t('Stage Image'),
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => 'This icon is what shows up on the Stage Landing Page.',
        'type' => 'image',
        'settings' => array(
            'uri_scheme' => 'public',
            'default_image' => FALSE,
            'user_register_form' => FALSE, // default
            'file_directory' => 'images', // default ''
            'file_extensions' => 'png gif jpg jpeg', // default
            'max_filesize' => '', // default
            'max_resolution' => '', // default
            'min_resolution' => '',  // default,
            'alt_field' => FALSE, // default
            'title_field' => FALSE, // default
        ),
        'widget' => array(
            'type' => 'image_image',
            'settings' => array(
            'progress_indicator' => 'bar', // default is 'throbber'
            'preview_image_style' => 'thumbnail', // default
            ),
        ),
        'bundles' => array(
            'lifecycle_stage'
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
