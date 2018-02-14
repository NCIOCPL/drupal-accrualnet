<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
$plugin = array(
  'single' => TRUE,  // Just do this one, it is needed.
  'title' => t('NCI Emergency Panel'),  // Title to show up on the pane screen.
  'description' => t('Displays an emergency if one exists'), // Description to show up on the pane screen.
  'category' => t('NCI'), // A category to put this under.
  'edit form' => 'nci_emergency_pane_custom_pane_edit_form', // A function that will return the settings form for the pane.
  'render callback' => 'nci_emergency_pane_custom_pane_render', // A function that will return the renderable content.
  'admin info' => 'nci_emergency_pane_custom_pane_admin_info', // A function that will return the information displayed on the admin screen (optional).
  'defaults' => array( // Array of defaults for the settings form.
    'url' => '',
  ),
  'all contexts' => TRUE, // This is NEEDED to be able to use substitution strings in your pane.
);

/**
 * An edit form for the pane's settings.
 */
function nci_emergency_pane_custom_pane_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
 
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Emergency URL'),
    '#description' => t('The URL to pull the emergency from (web service URL).'),
    '#default_value' => $conf['url'] ? $conf['url'] : variable_get('nci_emergency_url'),
  );
 
  return $form;
}
 
/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 * Notice, the magic that automatically does that for you.
 */
function nci_emergency_pane_custom_pane_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 * 
 * Checks to see if the URL in the panel is set - if not use the default. 
 * 
 * Returns the output of the nci_emergency_message in the block.
 */
function nci_emergency_pane_custom_pane_render($subtype, $conf, $args, $contexts) {
 
    $url = isset($conf['url']) ? $conf['url'] : FALSE;
    
  $output = nci_emergency_message($url);
  
  $block = new stdClass();
 
  $block->content = $output;
 
  return $block;
}
