<?php
/* * ***
 * Created By: Lauren
 * Created On: June 29, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */


$GLOBALS['an_resource_citation_fields_A'] = array(
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

$GLOBALS['an_resource_citation_fields_B'] = array(
        'organization' => array(),
        'date' => array(),
    );
    
    // Overwrite default citation fields for Type C
    $GLOBALS['an_resource_citation_fields_C'] = array(
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
        'location' => array(
            'label' => 'Meeting Location',
        ),
    );

/*
 * Internal Function
 * 
 * Checks to see if there is an overwrite, if not, returns default.
 */
function _resource_citation_change ($key, $changes, $defaults) {
    if (array_key_exists($key, $changes)) {
        return $changes[$key];
    } else {
        return $defaults[$key];
    }
}



/*
 * Internal Function
 * 
 * Determines what type of Citation a Resource uses and feeds the changes based 
 * off that. For example, the default title of date2 is Citation Second Date, 
 * but on the instance level of a Journal Article/Journal Review Article/etc for
 * Type A, the second date field is actually the Citation's EPub Date.
 */
function _resource_instance_citation_get ($defaults, $type) {
    global $an_resource_citation_fields_A, $an_resource_citation_fields_B, $an_resource_citation_fields_C;
    // Overwrite default citation fields for Type A
    /*$citation_fields_A = array(
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
    
    // Overwrite default citation fields for Type B
    $citation_fields_B = array(
        'organization' => array(),
        'date' => array(),
    );
    
    // Overwrite default citation fields for Type C
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
    );*/

    // Depending on what type of resource we have, apply the appropriate
    // citation changes (Cases may change if types.inc has changes)
    switch ($type) {
        case 'A': return _resource_instance_citation_type($defaults, $an_resource_citation_fields_A);
        case 'B': return _resource_instance_citation_type($defaults, $an_resource_citation_fields_B);
        case 'C': return _resource_instance_citation_type($defaults, $an_resource_citation_fields_C);
    }
}



/*
 * Internal Function
 * 
 * Is fed default citation fields and the changes for that type of citation.
 * Then, constructs an instance based on that.
 */
function _resource_instance_citation_type($defaults, $citation) {
    // Variables
    $instances = array();

    // If we're not fed a set of completely blank changes
    // (This would most likely mean that Citation Type was never found.)
    // This was added during debugging, but should be kept as the foreach
    // loop will create a code error if handed nothing at all. A new Type
    // that uses all the defaults should be declared as  = array()
    if ($citation != NULL) {
        foreach ($citation as $instance => $changes) {
            $newInstance = &$instances[]; // Instances don't need to be identified with a [$name]
            $newInstance['field_name'] = 'field_citation_' . _resource_citation_change('field_name', $changes, $defaults[$instance]);
            $newInstance['label'] = _resource_citation_change('label', $changes, $defaults[$instance]);
        }
    }
    
    // Return the instances for this citation type
    return $instances;
}

?>
