<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *Note* These fields are the same as the one created in other modules. This is not
 * an issue because it checks for existance before creating it. Which ever module is 
 * turned on first will create it. 
 * @global type $GLOBALS['an_lifecycle_fields']
 * @name $an_lifecycle_fields 
 */
$GLOBALS['an_homepage_fields'] = array(
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
                'homepage'
            ),
        ),
    array(
        'label' => t('Featured Carousel'),
        'field_name' => 'featured_carousel',
        'description' => '',
        'type' => 'entityreference',
        'cardinality' => '3',
        'entity_type' => 'node',
        'settings' => array(
            'target_type' => 'node',
            'handler_settings' => array('target_bundles' => array('featured_content_carousel')),
        ),
        'widget' => array(
            'type' => 'autocomplete',
        ),
        'bundles' => array(
            'homepage'
        ),
    ),
    array(
        'field_name' => 'landing_page_image',
        'label' => t('Homepage Image'),
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
            'homepage'
        ),
    ),
    array(
        'label' => t('Content Blocks'),
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
            'homepage',
        ),
    ),
);


/**
 *Returns array of fields containing only information needed to create the field.
 * @global type $an_lifecycle_fields
 * @return string 
 */
function _an_homepage_fields() {
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
