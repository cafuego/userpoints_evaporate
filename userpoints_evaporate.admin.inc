<?php
// $Id: userpoints_evaporate.admin.inc,v 1.1 2010/12/21 01:04:33 cafuego Exp $
/**
 * Display the settings form.
 */
function userpoints_evaporate_admin_settings() {

  $options = array(
    USERPOINTS_EVAPORATE_HOUR => t('Once an hour'),
    USERPOINTS_EVAPORATE_DAY => t('Once a day'),
    USERPOINTS_EVAPORATE_WEEK => t('Once a week'),
  );

  // Load the userpoints vocabulary, so evaporate can be configured per term. Wahey!
  $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE module='userpoints'"));
  $terms = taxonomy_get_tree($vid);

  // Grab existing settings.
  $settings = variable_get('userpoints_evaporate', array());

  $form['userpoints_evaporate'] = array(
    '#tree' => TRUE,
  );

  // Duplicate the evaporate settings for each term, and add an on/off radio button.
  //
  foreach ($terms as $term) {

    $form['userpoints_evaporate'][$term->tid] = array(
      '#type' => 'fieldset',
      '#title' => check_plain($term->name),
      '#description' => t('Control evaporation settings for %term points.', array('%term' => $term->name)),
      '#collapsible' => TRUE,
      '#collapsed' => ($settings[$term->tid]['enabled']) ? FALSE : TRUE,
    );

    $form['userpoints_evaporate'][$term->tid]['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Enabled',
      '#description' => t('Control whether or not %term points should evaporate.', array('%term' => $term->name)),
      '#options' => array(0, 1),
      '#default_value' => $settings[$term->tid]['enabled'],
    );

    $form['userpoints_evaporate'][$term->tid]['interval'] = array(
      '#title' => 'Interval',
      '#description' => t('How quickly do %term points evaporate?', array('%term' => $term->name)),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => ($settings[$term->tid]['interval']) ? $settings[$term->tid]['interval'] : USERPOINTS_EVAPORATE_DAY,
    );

    $form['userpoints_evaporate'][$term->tid]['number'] = array(
      '#title' => 'Number',
      '#description' => t('How many %term points evaporate at once?', array('%term' => $term->name)),
      '#type' => 'select',
      '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 6, 7 => 7, 8 =>8, 9 => 9, 10 => 10),
      '#default_value' => ($settings[$term->tid]['number']) ? $settings[$term->tid]['number'] : 1,
    );

    $form['userpoints_evaporate'][$term->tid]['description'] = array(
      '#title' => 'Description',
      '#description' => t('An optional description to be added in \'My points\' when %term points are evaporated.', array('%term' => $term->name)),
      '#type' => 'textfield',
      '#default_value' => $settings[$term->tid]['description'],
    );

    $form['userpoints_evaporate'][$term->tid]['inactive'] = array(
      '#title' => 'Inactive',
      '#type' => 'fieldset',
    );

    $form['userpoints_evaporate'][$term->tid]['inactive']['enabled'] = array(
      '#title' => 'Inactive Users Only',
      '#description' => t('Should users be inactive for a certain time before they start losing %term points?', array('%term' => $term->name)),
      '#type' => 'checkbox',
      '#options' => array(0, 1),
      '#default_value' => ($settings[$term->tid]['inactive']['enabled']) ? $settings[$term->tid]['inactive']['enabled'] : 0,
    );


    $form['userpoints_evaporate'][$term->tid]['inactive']['delta'] = array(
      '#title' => 'Inactivity Interval',
      '#description' => t('Enter a positive number.'),
      '#type' => 'textfield',
      '#size' => 3,
      '#default_value' => ($settings[$term->tid]['inactive']['delta']) ? $settings[$term->tid]['inactive']['delta'] : 1,
    );

    $form['userpoints_evaporate'][$term->tid]['inactive']['unit'] = array(
      '#title' => 'Inactivity Unit',
      '#type' => 'select',
      '#options' => array(
        USERPOINTS_EVAPORATE_HOUR => t('Hour(s)'),
        USERPOINTS_EVAPORATE_DAY => t('Day(s)'),
        USERPOINTS_EVAPORATE_WEEK => t('Week(s)'),
        USERPOINTS_EVAPORATE_MONTH => t('Month(s)'),
      ),
      '#default_value' => ($settings[$term->tid]['inactive']['unit']) ? $settings[$term->tid]['inactive']['unit'] : USERPOINTS_EVAPORATE_DAY,
    );
  }

  return system_settings_form($form);
}

/**
 * Validation handler for the settings form.
 */
function userpoints_evaporate_admin_settings_validate($form, &$form_state) {
  // Load the userpoints vocabulary, so evaporate can be configured per term. Wahey!
  $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE module='userpoints'"));
  $terms = taxonomy_get_tree($vid);

  foreach ($terms as $term) {
    if (!empty($form_state['values']['userpoints_evaporate'][$term->tid]['inactive']['enabled'])) {
      if (!is_numeric($form_state['values']['userpoints_evaporate'][$term->tid]['inactive']['delta']) || intval($form_state['values']['userpoints_evaporate'][$term->tid]['inactive']['delta']) < 1) {
        form_set_error('userpoints_evaporate][' . $term->tid . '][inactive][delta', t('Please enter a positive number'));
      }
    }
  }
}
