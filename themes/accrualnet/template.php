<?php

/**
 * @file
 * Contains functions to alter Drupal's markup for the AccrualNet theme.
 *
 */
// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('accrualnet_rebuild_registry') && !defined('MAINTENANCE_MODE')) {
	// Rebuild .info data.
	system_rebuild_theme_data();
	// Rebuild theme registry.
	drupal_theme_rebuild();
}

/**
 * Implements HOOK_theme().
 */
function accrualnet_theme(&$existing, $type, $theme, $path) {
	include_once './' . drupal_get_path('theme', 'accrualnet') . '/accrualnet-internals/template.theme-registry.inc';
	$items = _accrualnet_theme($existing, $type, $theme, $path);

	$items['user_login'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-login',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_login'
		),
	);
	$items['user_pass'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-pass',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_pass'
		),
	);
	$items['user_register_form'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-register-form',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_register_form'
		),
	);
	$items['user_profile_form'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-profile-form',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_profile_form'
		),
	);

	return $items;
}

function accrualnet_pager($variables) {
	// change 'quantity' to 5
        if($variables['quantity'] >= 9){
            $variables['quantity'] = 5;
        }

	// now call the default pager theme
	return theme_pager($variables);
}

function accrualnet_preprocess_user_profile(&$vars) {
    
}

function accrualnet_preprocess_user_picture(&$vars) {
	
}

function accrualnet_preprocess_user_profile_item(&$vars) {

}

function accrualnet_preprocess_user_login(&$vars) {
	
}

function accrualnet_preprocess_user_pass(&$vars) {
	
}

function accrualnet_preprocess_user_register_form(&$vars) {
	$vars['form']['account']['name']['#title'] = "Username";
	$vars['form']['picture']['picture_upload']['#description'] = "You can upload a JPG, GIF, or PNG file.\n(File size limit is 2MB)";
	$vars['form']['account']['name']['#description'] = 'This username will be displayed to all registered users if you participate in conversations or make comments on resources';
	$vars['form']['picture']['picture_upload']['#size'] = 0;
	$vars['form']['profile_color']['und']['#description'] = '';
	/*
	  $vars['form']['account']['pass']['#title'] = t('Password');
	  unset($vars['form']['account']['pass']['pass1']['#title']);
	  unset($vars['form']['account']['pass']['pass2']['#title']);

	  unset($vars['form']['picture']['#theme_wrappers']);
	  unset($vars['form']['picture']['select_avatar']['#title']);

	  $elements = array(
	  array(
	  'element' => & $vars['form']['account']['name'],
	  'desc' => 'This username will be displayed to all registered users ' .
	  'if you participate in conversations or make comments on resources.'
	  ),
	  array(
	  'element' => & $vars['form']['account']['mail'],
	  'desc' => 'Please enter a professional email address.'
	  ),
	  array(
	  'element' => & $vars['form']['account']['pass'],
	  'desc' => 'Please enter a password containing both letters and numbers.'
	  ),
	  array(
	  'element' => & $vars['form']['field_role']['und']['select'],
	  'desc' => 'Please select from the list the description that best ' .
	  'describes your occupation.'
	  ),
	  array(
	  'element' => & $vars['form']['field_years_in_research']['und'],
	  'desc' => 'Please enter the number of years in your field or at ' .
	  'your institution.'
	  ),
	  array(
	  'element' => & $vars['form']['field_institution_type']['und']['select'],
	  'desc' => 'Please select from the list the description that best ' .
	  'describes your institution.'
	  ),
	  array(
	  'element' => & $vars['form']['field_areas_of_interest']['und']['select'],
	  'desc' => 'Please select one or more areas of interest.'
	  ),
	  array(
	  'element' => & $vars['form']['picture']['picture_upload'],
	  'desc' => 'This profile picture will be viewable by all registered ' .
	  'users. Please select a picture to upload or select an avatar.'
	  ),
	  );

	  foreach ($elements as $element) {
	  _accrualnet_hover_desc($element['element'], $element['desc']);
	  } */
}


function _minimum_password_length_validate (&$form, &$form_state) {
    $newPass = $form_state['values']['pass'];
    if (!empty($newPass)) {
        if (strlen($newPass) < 5) {
            form_set_error('pass', 'Your password must contain a minimum of 6 characters.');
        }
    }
}
function accrualnet_form_user_register_form_alter (&$form, &$form_state) {
    $form['#validate'][] = '_minimum_password_length_validate';
}
function accrualnet_form_user_profile_form_alter(&$form, &$form_state) {
    $form['#validate'][] = '_minimum_password_length_validate';
}
/**
 * Moves the element's description (if any) to the #hover_desc key.
 * @param <type> $element the element to alter.
 * @param <type> $desc an overriding description, if desired.
 */
function _accrualnet_hover_desc(&$element, $desc = '') {
	if (empty($desc)) {
		// lift the existing description
		$desc = $element['#description'];
	}

	unset($element['#description']);

	$element['#hover_desc'] = $desc;
}

function accrualnet_form_required_marker ($variables) {
    // Added by Lauren (cleaning up my horrible jQuery required's)
      // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'form-required', 
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '><img alt="'.$attributes['title'].'" class="required-img" src="/'. path_to_theme() . '/accrualnet-internals/images/global/required.png" /></span>';
}

function accrualnet_preprocess_user_profile_form(&$vars) {

	try {
		hide($vars['form']['timezone']);
		hide($vars['form']['group_audience']);
		$vars['form']['account']['name']['#title'] = "Username";
		$vars['form']['account']['name']['#description'] = 'This username will be displayed to all registered users if you participate in conversations or make comments on resources';
		$vars['form']['account']['mail']['#description'] = 'Please enter a valid, work-related e-mail address.  All e-mails from the system will be sent to this address.  Your e-mail address is not made public, and will only be used if you wish to receive a new password or certain site-related notifications.';
		$vars['form']['account']['current_pass']['#description'] = '';
		$vars['form']['account']['pass']['#description'] = 'Please enter a password containing both letters and numbers. Your password must contain a minimum of 6 characters.';

		$vars['form']['account']['pass']['pass1']['#title'] = 'New Password';
		$vars['form']['account']['pass']['pass2']['#title'] = 'Re-Type New Password';

		$vars['form']['picture']['#title'] = '';
		hide($vars['form']['picture']['picture_delete']);

		$vars['form']['profile_color']['und']['#description'] = '';

		$vars['form']['picture']['picture_upload']['#size'] = 0;
		$vars['form']['picture']['picture_upload']['#description'] =
				"You can upload a JPG, GIF, or PNG file.\n(File size limit is 2MB)";
		$vars['form']['picture']['picture_upload']['#title'] = 'Upload Photo';
                
		//$vars['form']['picture']['select_avatar']['#title'] = 'Or Select an Avatar';
		//$vars['form']['picture']['#attached']['js'] = array(
		//	drupal_get_path('theme', 'accrualnet') . '/js/photo_crop.js',
		//);
		
                
                /* 508
                foreach ($vars['form'] as $formEle) {
                    if (array_key_exists('#type', $formEle)) {
                        if ($formEle['#type'] == 'container') {
                            
                        }
                    }
                }*/
	} catch (Exception $e) {
		print_r($e->getMessage());
	}
}
function accrualnet_form_element($variables) {
    /*
 * moved to functions for individual elements
    // Added by Lauren for 508 compliance
    if (array_key_exists('#type', $variables['element'])) {
        if ($variables['element']['#type'] == 'checkboxes') {
            //$required = !empty($variables['element']['#required']) ? theme('form_required_marker', array('element' => $variables['element'])) : '';
            //$variables['element']['#field_prefix'] = '<fieldset class="checkboxes-508"><legend class="checkboxes-508">' . $required . ' ' . $variables['element']['#title'] . '</legend>';
            //$variables['element']['#field_suffix'] = '</fieldset>';
        }
        if ($variables['element']['#type'] == 'managed_file') {
            
        }
    }
 * 
 */

        if (array_key_exists('#field_name', $variables['element'])) {
        if ($variables['element']['#field_name'] == 'group_audience') {
            if ($variables['element']['#children'] == null) {
                $variables['element']['#children'] = '<select class="hidden-508" id="' . $variables['element']['#id'] .'"></select>';
            }
        }
        }

        if ($variables['element']['#id'] == 'edit-keys') {
            
                $variables['element']['#children'] = '<label class="hidden-508" for="' . $variables['element']['#id'] .'">Edit Keys</label>'
                . $variables['element']['#children'];
            
        }
        
    
    return theme_form_element($variables);

}



function accrualnet_radios($variables) {
    // Added by Lauren for 508 compliance
    $required = !empty($variables['element']['#required']) ? theme('form_required_marker', array('element' => $variables['element'])) : '';
    $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'] = 'form-radios';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  $attributes['class'] .= ' radios-508';
  return '<fieldset ' . drupal_attributes($attributes) . '><legend class="radios-508">' . $required . ' ' . $variables['element']['#title'] . '</legend> ' . (!empty($element['#children']) ? $element['#children'] : '') . '</fieldset>';
}

function accrualnet_file($variables) {
    // Added by Lauren for 508
      $element = $variables['element'];
  $element['#attributes']['type'] = 'file';
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-file'));
  
  // Only needs 508 compliance help when the label is "invisible"
  if ($element['#title_display'] == 'invisible')
  return '<label class="hidden-508" for="'.$element['#id'].'">'.$element['#title'].'</label><input' . drupal_attributes($element['#attributes']) . ' />';
  else
  return '<input' . drupal_attributes($element['#attributes']) . ' />';    
}

function accrualnet_checkbox($variables) {
  return theme_checkbox($variables);
}
function accrualnet_textarea($variables) {
    // 508 compliance stuff - Lauren
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    drupal_add_library('system', 'drupal.textarea');
    $wrapper_attributes['class'][] = 'resizable';
  }
$output = '';
if ($element['#title'] == null || strlen($element['#title']) < 1) {
    $output .= '<label class="hidden-508" for=' . $element['#id'] . '>Textarea for '.$element['#field_name'].'</label>';
}
  $output .= '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

function accrualnet_checkboxes($variables) {
    //Added by Lauren for 508 compliance
    $required = !empty($variables['element']['#required']) ? theme('form_required_marker', array('element' => $variables['element'])) : '';
    //$variables['element']['#field_prefix'] = '<fieldset class="checkboxes-508"><legend class="checkboxes-508">' . $required . ' ' . $variables['element']['#title'] . '</legend>';
    //$variables['element']['#field_suffix'] = '</fieldset>';
    
    $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'][] = 'form-checkboxes';
  $attributes['class'][] = 'checkboxes-508';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<fieldset ' . drupal_attributes($attributes) . '><legend class="checkboxes-508">' . $required . ' ' . $variables['element']['#title'] . '</legend>' . (!empty($element['#children']) ? $element['#children'] : '') . '</fieldset>';
    //return theme_checkboxes($variables);
}

function accrualnet_form_element_label($variables) {

    $element = $variables['element'];
    // This is also used in the installer, pre-database setup.
    $t = get_t();

    // If title and required marker are both empty, output no label.
    if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
        return '';
    }

    // If the element is required, a required marker is appended to the label.
    $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

    $title = filter_xss_admin($element['#title']);

    $attributes = array();
    // Style the label as class option to display inline with the element.
    if ($element['#title_display'] == 'after') {
        $attributes['class'] = 'option';
    }
    // Show label only to screen readers to avoid disruption in visual flows.
    elseif ($element['#title_display'] == 'invisible') {
        $attributes['class'] = 'element-invisible';
    }

    if (!empty($element['#id'])) {
        $attributes['for'] = $element['#id'];
    }

    // calculate the description element prior to building the label
    $desc = '';
    if (!empty($element['#hover_desc'])) {
        //$desc = '<div class="description">' . $element['#description'] . "</div>\n";
        $desc = ' <img alt="ToolTip" src="/sites/accrualnet.cancer.gov/themes/accrualnet/tooltip.png" title="' . $element['#hover_desc'] . '">';
    }

    // string describing the label format
    $format = '!title !required !desc';

    // move the required field if desc exists
    if (!empty($desc))
        $format = '!required !title !desc';


    if (($element['#type'] == 'checkboxes') || ($element['#type'] == 'radios')) {
        return '';
    }
    elseif ($element['#type'] == 'managed_file') {
        $attributes['class'][] = 'label-508';
        return '<span ' . drupal_attributes($attributes) . '>'
        . $t($format, array('!title' => $title, '!required' => $required, '!desc' => $desc))
        . "</span>\n";
    }
    else {
        // The leading whitespace helps visually separate fields from inline labels.
        return ' <label' . drupal_attributes($attributes) . '>' .
        $t($format, array('!title' => $title, '!required' => $required, '!desc' => $desc)) .
        "</label>\n";
    }
}

function accrualnet_preprocess_search_results(&$variables) {
	// define the number of results being shown on a page
	$itemsPerPage = 10;

	$searchTerm = request_path();
	$searchTerm = ltrim(substr($searchTerm, strrpos($searchTerm, '/')), '/');

	global $pager_total_items;
	if ($pager_total_items != null) {
		// get the total number of results from the $GLOBALS
		$total = $pager_total_items[0];
	} else {
		$total = 0;
	}



	// set this html to the $variables
	//if ($total > 1 || $total == 0) {
	$variables['search_totals'] = '"' . $searchTerm . '" <span class="results-number">(' . $total . ')</span>';
	/* } else {
	  $variables['search_totals'] = "\"$searchTerm\" gave $total result";
	  } */
}

// Added By Lauren July 19, 2012
function accrualnet_form_alter(&$form, &$form_state, $form_id) {
	// Added by Lauren July 19, 2012
	// TIR #1823
	if ($form_id == 'search_form') {
		// Remove the ability to have an advanced search
		//unset($form['advanced']);
		// Remove the "Enter your keywords" label for the search
		unset($form['basic']['keys']['#title']);
	}
        if ($form_id == 'og_ui_confirm_subscribe') {
            $group = $form['group']['#value'];
            drupal_set_title('Send a membership request to the '.$group->label.' Community Moderator.');
            drupal_add_js("(function ($) { $(document).ready(function(){
                $('input#edit-submit').attr('value', 'Request Membership');
                $('input#edit-submit').css('margin-top', '-2px');
                $('<br/>').insertBefore($('input#edit-submit'));
                });})(jQuery);", 'inline');
        }
}

function accrualnet_preprocess_search_result(&$vars) {
	
}

/* function accrualnet_search_page($results) {
  

  $output['prefix']['#markup'] = '<ol class="search-results">';

  foreach ($results as $entry) {
  $output[] = array(
  '#theme' => 'search_result',
  '#result' => $entry,
  '#module' => 'my_module_name',
  );
  }
  $output['suffix']['#markup'] = '</ol>' . theme('pager');

  return $output;
  } */

/**
 * Return a themed breadcrumb trail.
 *
 * @param $variables
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function accrualnet_breadcrumb($variables) {
       $links = array();
       $path = '';
	   $urlRequested = request_uri();
       $arguments = explode('/', $urlRequested);
       
	$breadcrumb = $variables['breadcrumb'];
        if(!array_key_exists(1, $breadcrumb) && in_array('literature', $arguments)
		&& $urlRequested != '/literature'){
           $breadcrumb[1] = '<a href="/literature">Literature &amp; Tools</a>';
       }
       elseif(!array_key_exists(1, $breadcrumb) && in_array('communities', $arguments)
	   && $urlRequested != '/communities'){
           $breadcrumb[1] = "<a href=\"/communities\">Communities and Conversations</a>";
           $group = og_context();
           if ($group) {
               $breadcrumb[2] = '<a href="'. url("node/" . $group->etid). '">' . $group->label . '</a>';
           }
       }
       elseif(!array_key_exists(1, $breadcrumb) && in_array('education', $arguments)
	   && $urlRequested != '/education'){
           $breadcrumb[1] = "<a href=\"/education\">Education & Training</a>";
       }
	$output = '';
	//if (empty($breadcrumb)) {
		$breadcrumb[0] = '<a href="/">AccrualNet</a>';
	//}
        foreach($breadcrumb as $index => $value) {
            
            if ($value == "<a href=\"/communities\">Communities</a>"){
                $breadcrumb[$index] = "<a href=\"/communities\">Communities and Conversations</a>";
            }
        }
	// Determine if we are to display the breadcrumb.
	$show_breadcrumb = theme_get_setting('accrualnet_breadcrumb');
	if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

		// Optionally get rid of the homepage link.
		$show_breadcrumb_home = theme_get_setting('accrualnet_breadcrumb_home');
		if (!$show_breadcrumb_home) {
			array_shift($breadcrumb);
		}

		// Return the breadcrumb with separators.
		if (!empty($breadcrumb)) {
			$breadcrumb_separator = theme_get_setting('accrualnet_breadcrumb_separator');
			$trailing_separator = $title = '';
			if (theme_get_setting('accrualnet_breadcrumb_title')) {
				$item = menu_get_item();
				if (!empty($item['tab_parent'])) {
					// If we are on a non-default tab, use the tab's title.
					$breadcrumb[] = check_plain($item['title']);
				} else {
					$breadcrumb[] = drupal_get_title();
				}
			} elseif (theme_get_setting('accrualnet_breadcrumb_trailing')) {
				$trailing_separator = $breadcrumb_separator;
			}

			// Provide a navigational heading to give context for breadcrumb links to
			// screen-reader users.
			if (empty($variables['title'])) {
				$variables['title'] = t('You are here');
			}
			// Unless overridden by a preprocess function, make the heading invisible.
			if (!isset($variables['title_attributes_array']['class'])) {
				$variables['title_attributes_array']['class'][] = 'element-invisible';
			}

			// Build the breadcrumb trail.
			$output = '<nav class="breadcrumb" role="navigation">';
			$output .= '<h2' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</h2>';
			$output .= '<ol><li>' . implode($breadcrumb_separator . '</li><li>', $breadcrumb) . $trailing_separator . '</li></ol>';
			$output .= '</nav>';
		}
	}

	return $output;
}

/**
 * Override or insert variables into the html template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered. This is usually "html", but can
 *   also be "maintenance_page" since accrualnet_preprocess_maintenance_page() calls
 *   this function to have consistent variables.
 */
function accrualnet_preprocess_html(&$variables, $hook) {
	// Add variables and paths needed for HTML5 and responsive support.
	$variables['base_path'] = base_path();
	$variables['path_to_accrualnet'] = drupal_get_path('theme', 'accrualnet');
	$html5_respond_meta = theme_get_setting('accrualnet_html5_respond_meta');
	$variables['add_respond_js'] = in_array('respond', $html5_respond_meta);
	$variables['add_html5_shim'] = in_array('html5', $html5_respond_meta);
	$variables['default_mobile_metatags'] = in_array('meta', $html5_respond_meta);

	// If the user is silly and enables accrualnet as the theme, add some styles.
	if ($GLOBALS['theme'] == 'accrualnet') {
		include_once './' . $variables['path_to_accrualnet'] . '/accrualnet-internals/template.accrualnet.inc';
		_accrualnet_preprocess_html($variables, $hook);
	}

	// Attributes for html element.
	$variables['html_attributes_array'] = array(
		'lang' => $variables['language']->language,
		'dir' => $variables['language']->dir,
	);

	// Send X-UA-Compatible HTTP header to force IE to use the most recent
	// rendering engine or use Chrome's frame rendering engine if available.
	// This also prevents the IE compatibility mode button to appear when using
	// conditional classes on the html tag.
	if (is_null(drupal_get_http_header('X-UA-Compatible'))) {
		drupal_add_http_header('X-UA-Compatible', 'IE=edge,chrome=1');
	}

	$variables['skip_link_anchor'] = theme_get_setting('accrualnet_skip_link_anchor');
	$variables['skip_link_text'] = theme_get_setting('accrualnet_skip_link_text');

	// Return early, so the maintenance page does not call any of the code below.
	if ($hook != 'html') {
		return;
	}

	// Classes for body element. Allows advanced theming based on context
	// (home page, node of certain type, etc.)
	if (!$variables['is_front']) {
		// Add unique class for each page.
		$path = drupal_get_path_alias($_GET['q']);
		// Add unique class for each website section.
		list($section, ) = explode('/', $path, 2);
		$arg = explode('/', $_GET['q']);
		if ($arg[0] == 'node' && isset($arg[1])) {
			if ($arg[1] == 'add') {
				$section = 'node-add';
			} elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
				$section = 'node-' . $arg[2];
			}
		}
		$variables['classes_array'][] = drupal_html_class('section-' . $section);
	}
	if (theme_get_setting('accrualnet_wireframes')) {
		$variables['classes_array'][] = 'with-wireframes'; // Optionally add the wireframes style.
	}
	// Store the menu item since it has some useful information.
	$variables['menu_item'] = menu_get_item();
	if ($variables) {
		//ADDED by Doyle to add menu class to body tag
		$item = menu_get_active_trail();
		if (count($item) > 1 &&
				// ADDED by Dan to catch missing 'link_title' key
		isset($item[1]['link_title'])) {
			$navTitle = $item[1]['link_title'];
			$variables['classes_array'][] = drupal_html_class('nav-section-' . $navTitle);
		}

		//End Added by Doyle
		switch ($variables['menu_item']['page_callback']) {
			case 'views_page':
				// Is this a Views page?
				$variables['classes_array'][] = 'page-views';
				break;
			case 'page_manager_page_execute':
			case 'page_manager_node_view':
			case 'page_manager_contact_site':
				// Is this a Panels page?
				$variables['classes_array'][] = 'page-panels';
				break;
		}
	}
        $status = drupal_get_http_header("status");  
        if($status == "404 Not Found") {
            unset($variables['classes_array'][3] );
        }
            
}

/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
function accrualnet_process_html(&$variables, $hook) {
	// Flatten out html_attributes.
	$variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Override or insert variables in the html_tag theme function.
 */
function accrualnet_process_html_tag(&$variables) {
	$tag = &$variables['element'];

	if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
		// Remove redundant type attribute and CDATA comments.
		unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);

		// Remove media="all" but leave others unaffected.
		if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
			unset($tag['#attributes']['media']);
		}
	}
}

/**
 * Implement hook_html_head_alter().
 */
function accrualnet_html_head_alter(&$head) {
	// Simplify the meta tag for character encoding.
	if (isset($head['system_meta_content_type']['#attributes']['content'])) {
		$head['system_meta_content_type']['#attributes'] = array('charset' => str_replace('text/html; charset=', '', $head['system_meta_content_type']['#attributes']['content']));
	}
}

/**
 * Override or insert variables into the page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function accrualnet_preprocess_page(&$variables, $hook) {
	// Find the title of the menu used by the secondary links.
	$secondary_links = variable_get('menu_secondary_links_source', 'user-menu');
	if ($secondary_links) {
		$menus = function_exists('menu_get_menus') ? menu_get_menus() : menu_list_system_menus();
		$variables['secondary_menu_heading'] = $menus[$secondary_links];
	} else {
		$variables['secondary_menu_heading'] = '';
	}
        
        //Added error handling for 404 page
        $status = drupal_get_http_header("status");  
        if($status == "404 Not Found") {
            unset($variables['page']['sidebar_first']);
            $variables['theme_hook_suggestions'][] = 'page__404';
        }
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function accrualnet_preprocess_maintenance_page(&$variables, $hook) {
	accrualnet_preprocess_html($variables, $hook);
	// There's nothing maintenance-related in accrualnet_preprocess_page(). Yet.
	//accrualnet_preprocess_page($variables, $hook);
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function accrualnet_process_maintenance_page(&$variables, $hook) {
	accrualnet_process_html($variables, $hook);
	// Ensure default regions get a variable. Theme authors often forget to remove
	// a deleted region's variable in maintenance-page.tpl.
	foreach (array('header', 'navigation', 'highlighted', 'help', 'content', 'sidebar_first', 'sidebar_second', 'footer', 'bottom') as $region) {
		if (!isset($variables[$region])) {
			$variables[$region] = '';
		}
	}
}

/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function accrualnet_preprocess_node(&$variables, $hook) {
	// Add $unpublished variable.
	$variables['unpublished'] = (!$variables['status']) ? TRUE : FALSE;

	// Add pubdate to submitted variable.
	$variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['node']->created, 'custom', 'c') . '">' . $variables['date'] . '</time>';
	if ($variables['display_submitted']) {
		$variables['submitted'] = t('Submitted by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['pubdate']));
	}

	// Add a class for the view mode.
	if (!$variables['teaser']) {
		$variables['classes_array'][] = 'view-mode-' . $variables['view_mode'];
	}

	// Add a class to show node is authored by current user.
	if ($variables['uid'] && $variables['uid'] == $GLOBALS['user']->uid) {
		$variables['classes_array'][] = 'node-by-viewer';
	}

	$variables['title_attributes_array']['class'][] = 'node-title';
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
function accrualnet_preprocess_comment(&$variables, $hook) {
	// If comment subjects are disabled, don't display them.
	if (variable_get('comment_subject_field_' . $variables['node']->type, 1) == 0) {
		$variables['title'] = '';
	}

	// Add pubdate to submitted variable.
	$variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['comment']->created, 'custom', 'c') . '">' . $variables['created'] . '</time>';
	$variables['submitted'] = t('!username replied on !datetime', array('!username' => $variables['author'], '!datetime' => $variables['pubdate']));

	// Zebra striping.
	if ($variables['id'] == 1) {
		$variables['classes_array'][] = 'first';
	}
	if ($variables['id'] == $variables['node']->comment_count) {
		$variables['classes_array'][] = 'last';
	}
	$variables['classes_array'][] = $variables['zebra'];

	$variables['title_attributes_array']['class'][] = 'comment-title';
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
function accrualnet_preprocess_region(&$variables, $hook) {
	// Sidebar regions get some extra classes and a common template suggestion.
	if (strpos($variables['region'], 'sidebar_') === 0) {
		$variables['classes_array'][] = 'column';
		$variables['classes_array'][] = 'sidebar';
		// Allow a region-specific template to override accrualnet's region--sidebar.
		array_unshift($variables['theme_hook_suggestions'], 'region__sidebar');
	}
	// Use a template with no wrapper for the content region.
	elseif ($variables['region'] == 'content') {
		// Allow a region-specific template to override accrualnet's region--no-wrapper.
		array_unshift($variables['theme_hook_suggestions'], 'region__no_wrapper');
	}
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function accrualnet_preprocess_block(&$variables, $hook) {
	// Use a template with no wrapper for the page's main content.
	if ($variables['block_html_id'] == 'block-system-main') {
		$variables['theme_hook_suggestions'][] = 'block__no_wrapper';
	}

	// Classes describing the position of the block within the region.
	if ($variables['block_id'] == 1) {
		$variables['classes_array'][] = 'first';
	}
	// The last_in_region property is set in accrualnet_page_alter().
	if (isset($variables['block']->last_in_region)) {
		$variables['classes_array'][] = 'last';
	}
	$variables['classes_array'][] = $variables['block_zebra'];

	$variables['title_attributes_array']['class'][] = 'block-title';

	// Add Aria Roles via attributes.
	switch ($variables['block']->module) {
		case 'system':
			switch ($variables['block']->delta) {
				case 'main':
					// Note: the "main" role goes in the page.tpl, not here.
					break;
				case 'help':
				case 'powered-by':
					$variables['attributes_array']['role'] = 'complementary';
					break;
				default:
					// Any other "system" block is a menu block.
					$variables['attributes_array']['role'] = 'navigation';
					break;
			}
			break;
		case 'menu':
		case 'menu_block':
		case 'blog':
		case 'book':
		case 'comment':
		case 'forum':
		case 'shortcut':
		case 'statistics':
			$variables['attributes_array']['role'] = 'navigation';
			break;
		case 'search':
			$variables['attributes_array']['role'] = 'search';
			break;
		case 'help':
		case 'aggregator':
		case 'locale':
		case 'poll':
		case 'profile':
			$variables['attributes_array']['role'] = 'complementary';
			break;
		case 'node':
			switch ($variables['block']->delta) {
				case 'syndicate':
					$variables['attributes_array']['role'] = 'complementary';
					break;
				case 'recent':
					$variables['attributes_array']['role'] = 'navigation';
					break;
			}
			break;
		case 'user':
			switch ($variables['block']->delta) {
				case 'login':
					$variables['attributes_array']['role'] = 'form';
					break;
				case 'new':
				case 'online':
					$variables['attributes_array']['role'] = 'complementary';
					break;
			}
			break;
	}
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function accrualnet_process_block(&$variables, $hook) {
	// Drupal 7 should use a $title variable instead of $block->subject.
	$variables['title'] = $variables['block']->subject;
}

/**
 * Implements hook_page_alter().
 *
 * Look for the last block in the region. This is impossible to determine from
 * within a preprocess_block function.
 *
 * @param $page
 *   Nested array of renderable elements that make up the page.
 */
function accrualnet_page_alter(&$page) {
	// Look in each visible region for blocks.
	foreach (system_region_list($GLOBALS['theme'], REGIONS_VISIBLE) as $region => $name) {
		if (!empty($page[$region])) {
			// Find the last block in the region.
			$blocks = array_reverse(element_children($page[$region]));
			while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
				array_shift($blocks);
			}
			if ($blocks) {
				$page[$region][$blocks[0]]['#block']->last_in_region = TRUE;
			}
		}
	}
}

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 *
 * Prevent user-facing field styling from screwing up node edit forms by
 * renaming the classes on the node edit form's field wrappers.
 */
function accrualnet_form_node_form_alter(&$form, &$form_state, $form_id) {
	// Remove if #1245218 is backported to D7 core.
	foreach (array_keys($form) as $item) {
		if (strpos($item, 'field_') === 0) {
			if (!empty($form[$item]['#attributes']['class'])) {
				foreach ($form[$item]['#attributes']['class'] as &$class) {
					if (strpos($class, 'field-type-') === 0 || strpos($class, 'field-name-') === 0) {
						// Make the class different from that used in theme_field().
						$class = 'form-' . $class;
					}
				}
			}
		}
	}
}


function accrualnet_form_search_form_alter(&$form, &$form_state, $form_id){
    $form['basic']['submit']['#attributes']['onClick'] = 'NCIAnalytics.SiteSearch(this.form);';
}

function accrualnet_form_search_block_form_alter(&$form, &$form_state, $form_id){
    //$test = $form;
    $form['actions']['submit']['#attributes']['onClick'] = 'NCIAnalytics.SiteSearch(this.form);';
    //$form['form']['actions']['submit']['#attributes']['onClick'] = 'alert("1234")';
    
}