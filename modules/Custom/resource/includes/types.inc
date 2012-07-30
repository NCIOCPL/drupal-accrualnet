<?php
/* * ***
 * Created By: Lauren
 * Created On: June 27, 2012
 *
 * Last Updated By: Lauren
 * Last Updated On: June 29, 2012
 * *** */

// Citation Types
// Separated into variables rather than consistent strings in case we ever find 
// a need to switch from String determination to an array listing of fields.
$A = 'A'; // You will need to change this also in citation.types.inc
$B = 'B'; // You will need to change this also in citation.types.inc
$C = 'C'; // You will need to change this also in citation.types.inc

$GLOBALS['an_education_types'] = array(
    'materials_staff',
    'materials_patient'
);
// All of the Resource Types
$GLOBALS['an_resource_types'] = array(
    'journal_article' => array(
        // Content Properties
        'name' => 'Journal Article',
        'description' => 'TBD',
        'title' => 'Article Title',
        // Field Properties
        'citation' => $A,
    ),
    'journal_review' => array(
        // Content Properties
        'name' => 'Journal Review Article',
        'description' => 'TBD',
        'title' => 'Article Title',
        // Field Properties
        'citation' => $A,
    ),
    'materials_forms' => array(
        // Content Properties
        'name' => 'Sample Materials and Forms',
        'description' => 'TBD',
        'title' => 'Form or Material Title',
        // Field Properties
        'citation' => $B,
    ),
    'materials_patient' => array(
        // Content Properties
        'name' => 'Patient Education Materials',
        'description' => 'TBD',
        'title' => 'Material Title',
        // Field Properties
        'citation' => $B,
    ),
    'materials_staff' => array(
        // Content Properties
        'name' => 'Staff Education Materials',
        'description' => 'TBD',
        'title' => 'Material Title',
        // Field Properties
        'citation' => $B,
    ),
    'meeting_abstract' => array(
        // Content Properties
        'name' => 'Meeting Abstract',
        'description' => 'TBD',
        'title' => 'Meeting Name',
        // Field Properties
        'citation' => $C,
    ),
   /*
    * Removed based on email jul 9
    *  'presentation' => array(
        // Content Properties
        'name' => 'Presentation',
        'description' => 'TBD',
        'title' => 'Title of Presentation',
        // Field Properties
        'citation' => $B,
    ),
    * 
    */    
    'report' => array(
        // Content Properties
        'name' => 'Report',
        'description' => 'TBD',
        'title' => 'Name of Report',
        // Field Properties
        'citation' => $A,
    ),
);
?>
