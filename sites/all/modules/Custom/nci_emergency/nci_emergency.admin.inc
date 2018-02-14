<?php

/*
 * Administration form to handle configuration of the emergency settings.
 * nci_emegency_url - the URL in which we get the emergency information from
 * nci_emergency_global_display - A flag to determine if the emergency is displayed
 * on every page or not.
 */
function nci_emergency_admin(){
    $form = array();
    
    $form['nci_emergency_url'] = array(
        '#type' => 'textfield',
        '#title' => t('NCI Emergency Web Service URL'),
        '#default_value' => variable_get('nci_emergency_url',  ''),
        '#size' => '100',
        '#description'=> t('Web Service URL for the Emergency tool - Expecting XML Result.'),
        '#required' => TRUE,
    );
    
    $form['nci_emergency_global_display'] = array(
        '#type' => 'checkbox',
        '#title' => t('Global Emergency Message'),
        '#description' => t('Select this if the emergency message should display 
            across the entire website.'),
        '#default_value' => variable_get('nci_emergency_global_display',  TRUE),
    );
  
    $form['nci_emergency_verifyssl'] = array(
        '#type' => 'textfield',
        '#title' => t('Verify SSL'),
        '#description' => t('Verify the SSL cert of the URL you are receiving an
            emergency from. (This should only be set to 0 in DEVELOPMENT environments, 2 in
            production environments. A value of 1 has been deprecated and will cause an error.'),
        '#default_value' => variable_get('nci_emergency_verifyssl',  2),
    );
    
    
    return system_settings_form($form);
}


?>
