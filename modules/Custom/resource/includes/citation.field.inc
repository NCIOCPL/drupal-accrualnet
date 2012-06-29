<?php
/* * ***
 * Created By: Lauren
 * Created On: June 28, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */

$GLOBALS['an_resource_field_citation'] = array(
    'author' => array(
        'label' => 'Author(s)',
        'field_name' => 'author',
        'type' => 'text',
        'cardinality' => FIELD_CARDINALITY_UNLIMITED,
    ),
    'name' => array(
        'label' => 'Resource Name',
        'field_name' => 'name',
        'type' => 'text',
        'cardinality' => 1,
    ),
    'date' => array(
        'label' => 'Citation Date',
        'field_name' => 'date',
        'type' => 'datestamp',
        'cardinality' => 1,
    ),
    'date2' => array(
        'label' => 'Citation Second Date',
        'field_name' => 'date2',
        'type' => 'datestamp',
        'cardinality' => 1,
    ),
    'volume' => array(
        'label' => 'Citation Volume',
        'field_name' => 'volume',
        'type' => 'text',
        'cardinality' => 1,
    ),
    'issue' => array(
        'label' => 'Citation Issue Number',
        'field_name' => 'issue',
        'type' => 'text',
        'cardinality' => 1,
    ),
    'pages' => array(
        'label' => 'Citation Page(s)',
        'field_name' => 'pages',
        'type' => 'text',
        'cardinality' => 1,
    ),
    'organization' => array(
        'label' => 'Citation Organization',
        'field_name' => 'organization',
        'type' => 'text',
        'cardinality' => 1,
    ),
    'location' => array(
        'label' => 'Citation Location',
        'field_name' => 'location',
        'type' => 'text',
        'cardinality' => 1,
    ),
);

module_load_include('inc', 'resource', 'includes/citation.types');


function _resource_field_citation () {
    // Variables
    global $an_resource_field_citation;
    $fields = array();
    
    // Setup the Global fields
    foreach ($an_resource_field_citation as $field => $properties) {
        $fields['field_citation_'.$field]['field_name'] = 'field_citation_' . $an_resource_field_citation[$field]['field_name'];
        $fields['field_citation_'.$field]['type'] = $an_resource_field_citation[$field]['type'];
        $fields['field_citation_'.$field]['cardinality'] = $an_resource_field_citation[$field]['cardinality'];
    }

    return $fields;
}

function _resource_instance_citation ($citation) {
    // Variables
    global $an_resource_field_citation;
    $instances = _resource_instance_citation_get($an_resource_field_citation, $citation);
    return $instances;
}

function _resource_find_citation ($target) {
    global $an_resource_field_citation;
    $target = str_replace('field_citation_', '', $target);
    foreach ($an_resource_field_citation as $field) {
        if ($field['field_name'] == $target) {
            return true;
        }
    }
    return false;
}
?>
