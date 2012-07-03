<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 * TODO: Move items per page configuration to an admin menu.
 * 
 *  */



function resource_landing_page() {
    
 // Now let's build the output for this page
    $output = '<div id="allConversations">';
    $output .= '<ul>';
    $output .= '</ul>';

    // Add the pager
    $output .= theme('pager');

    $output .= '</div>';
    return $output;
 
}
