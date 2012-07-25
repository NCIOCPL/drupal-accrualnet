<?php
/* * ***
 * Created By: Doyle
 * Created On: July 1, 2012
 *
 * Last Updated By: Doyle
 * Last Updated On: July 12, 2012
 * *** */


/**
 * Define types needed by the lifecycle section of the AN Site
 * @global type $GLOBALS['an_lifecycle_types']
 * @name $an_lifecycle_types 
 */
$GLOBALS['an_lifecycle_types'] = array(
    'lifecycle_stage' => array(
        // Content Properties
        'name' => 'Lifecycle Stage',
        'description' => 'TBD',
        'title' => 'Stage Name',
    ),
    'lifecycle_strategy' => array(
        // Content Properties
        'name' => 'Lifecycle Strategy',
        'description' => 'TBD',
        'title' => 'Strategy Name',
    ),
    'landing_page' => array(
        'name' => 'Landing Page',
        'description' => 'A landing page item (1st level navigation page).',
        'title' => 'Landing Page'
    )
    
);
?>
