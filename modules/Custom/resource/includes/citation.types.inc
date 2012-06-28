<?php

/*$GLOBALS['citation_fields_A'] = array(
    'author' => array(),
    'name' => array(
        'label' => 'Name of Journal',
    ),
    'date' => array(),
    'volume' => array(),
    'issue' => array(),
    'pages' => array(),
    'date2' => array(
        'label' => 'Citation EPub Date',
    ),
);
$GLOBALS['citation_fields_B'] = array(
    'organization' => array(),
    'date' => array(),
);
$GLOBALS['citation_fields_C'] = array(
    'author' => array(),
    'organization' => array(),
    'name' => array(
        'label' => 'Meeting Name',
    ),
    'date' => array (
        'label' => 'Date Meeting Began',
    ),
    'date2' => array (
        'label' => 'Date Meeting Ended',
    ),
    'location' => array(),
);*/

function _resource_citation_change ($key, $changes, $defaults) {
    if (array_key_exists($key, $changes)) {
        return $changes[$key];
    } else {
        return $defaults[$key];
    }
}

/*

function _resource_field_citation_get ($defaults) {
    global $citation_fields_A, $citation_fields_B, $citation_fields_C;
    $fields = array();
    $fields = array_merge($fields, _resource_field_citation_type($defaults, $citation_fields_A));
    $fields = array_merge($fields, _resource_field_citation_type($defaults, $citation_fields_B));
    $fields = array_merge($fields, _resource_field_citation_type($defaults, $citation_fields_C));
    return $fields;
}
 * 
 */

function _resource_instance_citation_get ($defaults, $type) {
    $citation_fields_A = array(
        'author' => array(),
        'name' => array(
            'label' => 'Name of Journal',
        ),
        'date' => array(),
        'volume' => array(),
        'issue' => array(),
        'pages' => array(),
        'date2' => array(
            'label' => 'Citation EPub Date',
        ),
    );
    $citation_fields_B = array(
        'organization' => array(),
        'date' => array(),
    );
    $citation_fields_C = array(
        'author' => array(),
        'organization' => array(),
        'name' => array(
            'label' => 'Meeting Name',
        ),
        'date' => array(
            'label' => 'Date Meeting Began',
        ),
        'date2' => array(
            'label' => 'Date Meeting Ended',
        ),
        'location' => array(),
    );

    switch ($type) {
        case 'A': return _resource_instance_citation_type($defaults, $citation_fields_A);
        case 'B': return _resource_instance_citation_type($defaults, $citation_fields_B);
        case 'C': return _resource_instance_citation_type($defaults, $citation_fields_C);
    }
}

/*
function _resource_field_citation_type ($defaults, $citation) {
    // Variables
    $fields = array();

    // Create the fields
    if ($citation != NULL) {
    foreach ($citation as $field => $changes) {
        $fields[$field]['field_name'] = 'field_citation_' . _resource_citation_change('field_name', $changes, $defaults[$field]);
        $fields[$field]['type'] = _resource_citation_change('type', $changes, $defaults[$field]);
        $fields[$field]['cardinality'] = _resource_citation_change('cardinality', $changes, $defaults[$field]);
    }
    }
    
    // Return the fields
    return $fields;
}
 * 
 */

function _resource_instance_citation_type ($defaults, $citation) {
    // Variables
    $instances = array();

    // Create the instances
    if ($citation != NULL) {
    foreach ($citation as $instance => $changes) {
        $newInstance = &$instances[];
        $newInstance['field_name'] = 'field_citation_' . _resource_citation_change('field_name', $changes, $defaults[$instance]);
        $newInstance['label'] = _resource_citation_change('label', $changes, $defaults[$instance]);
    }
    }
    // Return the instances
    return $instances;
}

?>
