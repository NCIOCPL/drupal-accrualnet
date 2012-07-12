<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Sets up patuauto alias' for the lifecycle content types. 
 * @global type $GLOBALS['an_node_alias']
 * @name $an_node_alias 
 */
$GLOBALS['an_node_alias'] = array(
    'lifecycle_stage' => 'protocol_accrual_lifecycle/[node:system-title]',
    'lifecycle_strategy' => 'protocol_accrual_lifecycle/[node:parent-stage-system-title]/[node:system-title]',
);

?>