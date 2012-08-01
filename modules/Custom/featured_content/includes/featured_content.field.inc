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
    $resource_bundle_names[$type] = $type;

}

/**
 * Setup fields needed/used by the an_lifecycle section of the site. This includes
 * the related_strategy field which is palced on all resource types.
 * Contains information to create the field and the field instance.
 * @global type $GLOBALS['an_lifecycle_fields']
 * @name $an_lifecycle_fields 
 */
$GLOBALS['featured_content_fields'] = array(
    // Machine Name => Label
     array(
        'label' => 'Display Format',
        'description' => 'Please select the display format for this content module.',
        'field_name' => 'display_format',
        'required' => TRUE,
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'list_text',
        'settings' => array(
            'allowed_values' => array(
                'listing' => 'Content Listing',
                'listing_image' => 'Content Listing + Image',
            )
        ),
        'widget' => array(
            'type' => 'options_select',
        ),
        'bundles' => array(
            'dynamic_content_block',
        ),
    ),
    array(
        'label' => 'Order By',
        'description' => 'Please select how the results should be ordered.',
        'field_name' => 'order_by',
        'required' => TRUE,
        'cardinality' => '1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'list_text',
        'settings' => array(
            'allowed_values' => array(
                'alpha' => 'Alphabetical',
                'date_recent' => 'Most Recently Posted',
                'manual' => 'Manual Content Override'
            )
        ),
        'widget' => array(
            'type' => 'options_select',
        ),
        'bundles' => array(
            'dynamic_content_block',
        ),
    ),
    array(
        'label' => 'Featured Content Type(s)',
        'description' => 'Select the type of content you would like to feature',
        'field_name' => 'featured_type',
        'required' => TRUE,
        'cardinality' => '-1',
        'entity_type' => 'node',
        'description' => '',
        'type' => 'list_text',
        'settings' => array(
            'allowed_values' => array_merge($resource_bundle_names, array('conversation' => 'conversation'))
        ),
        'widget' => array(
            'type' => 'options_buttons',
        ),
        'bundles' => array(
            'dynamic_content_block',
        ),
    ),
   
    array(
        'label' => 'Manual Content Override',
        'field_name' => 'manual_content',
        'description' => '',
        'required' => FALSE,
        'type' => 'entityreference',
        'cardinality' => '-1',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array_merge($resource_bundle_names, array('conversation' => 'conversation'))),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'dynamic_content_block',
        ),
    ),
    array(
        'label' => 'Content Blocks',
        'field_name' => 'content_blocks',
        'description' => '',
        'required' => FALSE,
        'type' => 'entityreference',
        'cardinality' => '4',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array('dynamic_content_block','content_block')),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'featured_content_carousel',
        ),
    ),
    array(
            'label' => t('Content'),
            'description' => 'Provide the content for this page.',
            'field_name' => 'content',
            'type' => 'text_long',
            'cardinality' => 1,
            'entity_type' => 'node',
            'settings' => array(),
            'instance_settings' => array('text_processing' => 1), //Set the instance to be filtered html
            'bundles' => array(
                'content_block'
            ),
        ),
    
    array(
        'field_name' => 'featured_image',
        'label' => t('Featured Image'),
        'cardinality' => '1',
        'required' => FALSE,
        'entity_type' => 'node',
        'description' => 'The image that will display if Conent Listing + Image is selected',
        'type' => 'image',
        'settings' => array(
            'default_image' => FALSE,
            'user_register_form' => FALSE, // default
            'file_extensions' => 'png gif jpg jpeg', // default
            'max_filesize' => '', // default
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
            'dynamic_content_block',
            'content_block'
        ),
    ),
    array(
        'label' => t('Featured Carousel'),
        'field_name' => 'featured_carousel',
        'description' => '',
        'type' => 'entityreference',
        'cardinality' => '1',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array('featured_content_carousel')),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'landing_page',
            'lifecycle_stage'
        ),
    ),
    array(
        'label' => 'More Link',
        'field_name' => 'more_link',
        'description' => 'This link is only applicable for items displayed in the content areas at the bottom of the Homepage',
        'type' => 'link_field',
        'cardinality' => '1',
        'entity_type' => 'node',
        'settings' => array(),
        'bundles' => array(
            'dynamic_content_block',
        ),
    ),
    
);


/**
 *Returns array of fields containing only information needed to create the field.
 * @global type $an_lifecycle_fields
 * @return string 
 */
function _featured_content_fields() {
    // Variables
    global $featured_content_fields;
    $fields = array();
    
    // Create the fields
    foreach ($featured_content_fields as $field) {
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
