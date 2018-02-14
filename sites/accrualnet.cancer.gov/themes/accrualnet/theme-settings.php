<?php
/**
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function accrualnet_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  // Create the form using Forms API
  $form['breadcrumb'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Breadcrumb settings'),
  );
  $form['breadcrumb']['accrualnet_breadcrumb'] = array(
    '#type'          => 'select',
    '#title'         => t('Display breadcrumb'),
    '#default_value' => theme_get_setting('accrualnet_breadcrumb'),
    '#options'       => array(
                          'yes'   => t('Yes'),
                          'admin' => t('Only in admin section'),
                          'no'    => t('No'),
                        ),
  );
  $form['breadcrumb']['breadcrumb_options'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        ':input[name="accrualnet_breadcrumb"]' => array('value' => 'no'),
      ),
    ),
  );
  $form['breadcrumb']['breadcrumb_options']['accrualnet_breadcrumb_separator'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Breadcrumb separator'),
    '#description'   => t('Text only. Don’t forget to include spaces.'),
    '#default_value' => theme_get_setting('accrualnet_breadcrumb_separator'),
    '#size'          => 5,
    '#maxlength'     => 10,
  );
  $form['breadcrumb']['breadcrumb_options']['accrualnet_breadcrumb_home'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Show home page link in breadcrumb'),
    '#default_value' => theme_get_setting('accrualnet_breadcrumb_home'),
  );
  $form['breadcrumb']['breadcrumb_options']['accrualnet_breadcrumb_trailing'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Append a separator to the end of the breadcrumb'),
    '#default_value' => theme_get_setting('accrualnet_breadcrumb_trailing'),
    '#description'   => t('Useful when the breadcrumb is placed just before the title.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="accrualnet_breadcrumb_title"]' => array('checked' => TRUE),
      ),
      'unchecked' => array(
        ':input[name="accrualnet_breadcrumb_title"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['breadcrumb']['breadcrumb_options']['accrualnet_breadcrumb_title'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Append the content title to the end of the breadcrumb'),
    '#default_value' => theme_get_setting('accrualnet_breadcrumb_title'),
    '#description'   => t('Useful when the breadcrumb is not placed just before the title.'),
  );

  $form['support'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Accessibility and support settings'),
  );
  // Only toggle the layout for the main accrualnet theme.
  if ($form['var']['#value'] == 'theme_accrualnet_settings') {
    $form['support']['accrualnet_layout'] = array(
      '#type'          => 'radios',
      '#title'         => t('Layout'),
      '#options'       => array(
        'accrualnet-responsive-sidebars' => t('Responsive sidebar layout') . ' <small>(layouts/responsive-sidebars.css)</small>',
        'accrualnet-fixed-width' => t('Fixed width layout') . ' <small>(layouts/fixed-width.css)</small>',
      ),
      '#default_value' => theme_get_setting('accrualnet_layout'),
    );
  }
  $form['support']['accrualnet_skip_link_anchor'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Anchor ID for the “skip link”'),
    '#default_value' => theme_get_setting('accrualnet_skip_link_anchor'),
    '#field_prefix'  => '#',
    '#description'   => t('Specify the HTML ID of the element that the accessible-but-hidden “skip link” should link to. (<a href="!link">Read more about skip links</a>.)', array('!link' => 'http://drupal.org/node/467976')),
  );
  $form['support']['accrualnet_skip_link_text'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Text for the “skip link”'),
    '#default_value' => theme_get_setting('accrualnet_skip_link_text'),
    '#description'   => t('For example: <em>Jump to navigation</em>, <em>Skip to content</em>'),
  );
  $form['support']['accrualnet_html5_respond_meta'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Add HTML5 and responsive scripts and meta tags to every page.'),
    '#default_value' => theme_get_setting('accrualnet_html5_respond_meta'),
    '#options'       => array(
                          'respond' => t('Add Respond.js JavaScript to add basic CSS3 media query support to IE 6-8.'),
                          'html5' => t('Add HTML5 shim JavaScript to add support to IE 6-8.'),
                          'meta' => t('Add meta tags to support responsive design on mobile devices.'),
                        ),
    '#description'   => t('IE 6-8 require a JavaScript polyfill solution to add basic support of HTML5 and CSS3 media queries. If you prefer to use another polyfill solution, such as <a href="!link">Modernizr</a>, you can disable these options. Mobile devices require a few meta tags for responsive designs.', array('!link' => 'http://www.modernizr.com/')),
  );

  $form['themedev'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Theme development settings'),
  );
  $form['themedev']['accrualnet_rebuild_registry'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Rebuild theme registry on every page.'),
    '#default_value' => theme_get_setting('accrualnet_rebuild_registry'),
    '#description'   => t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>. WARNING: this is a huge performance penalty and must be turned off on production websites.', array('!link' => 'http://drupal.org/node/173880#theme-registry')),
  );
  $form['themedev']['accrualnet_wireframes'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Add wireframes around main layout elements'),
    '#default_value' => theme_get_setting('accrualnet_wireframes'),
    '#description'   => t('<a href="!link">Wireframes</a> are useful when prototyping a website.', array('!link' => 'http://www.boxesandarrows.com/view/html_wireframes_and_prototypes_all_gain_and_no_pain')),
  );
}
