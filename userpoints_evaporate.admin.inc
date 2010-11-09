<?php
/**
 * Display the settings form.
 */
function userpoints_evaporate_admin_settings() {

  $options = array(
    USERPOINTS_EVAPORATE_HOUR => t('Once an hour'),
    USERPOINTS_EVAPORATE_DAY => t('Once a day'),
    USERPOINTS_EVAPORATE_WEEK => t('Once a week'),
  );

  $form['userpoints_evaporate_interval'] = array(
    '#title' => 'Interval',
    '#description' => t('How quickly do userpoints evaporate?'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('userpoints_evaporate_interval', USERPOINTS_EVAPORATE_DAY),
  );
  $form['userpoints_evaporate_number'] = array(
    '#title' => 'Number',
    '#description' => t('How many points evaporate at once?'),
    '#type' => 'select',
    '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 6, 7 => 7, 8 =>8, 9 => 9),
    '#default_value' => variable_get('userpoints_evaporate_number', 1),
  );
  $form['userpoints_evaporate_description'] = array(
    '#title' => 'Description',
    '#description' => t('An optional description to be added in \'My points\' when points are evaporated.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('userpoints_evaporate_description', ''),
  );
  $form['userpoints_evaporate_inactive'] = array(
    '#title' => 'Inactive Users Only',
    '#description' => t('Should users be inactive for a certain time before they start losing points?'),
    '#type' => 'radios',
    '#options' => array(0 => 'No', 1 => 'Yes'),
    '#default_value' => variable_get('userpoints_evaporate_inactive', 0),
  );
  $form['userpoints_evaporate_inactive_value'] = array(
    '#title' => 'Set Interval',
    '#description' => t('How long must a user have been inactive before their points start evaporating? Please enter a number and choose an interval. Unless <em>Inactive Users Only</em> is set to <em>Yes</em>, these settings have no effect.'),
    '#type' => 'fieldset',
  );
  $form['userpoints_evaporate_inactive_value']['userpoints_evaporate_inactive_delta'] = array(
    '#title' => 'Interval',
    '#description' => t('Enter a positive number.'),
    '#type' => 'textfield',
    '#size' => 3,
    '#default_value' => variable_get('userpoints_evaporate_inactive_delta', 1),
  );
  $form['userpoints_evaporate_inactive_value']['userpoints_evaporate_inactive_unit'] = array(
    '#title' => 'Unit',
    '#type' => 'select',
    '#options' => array(
      USERPOINTS_EVAPORATE_HOUR => t('Hour(s)'),
      USERPOINTS_EVAPORATE_DAY => t('Day(s)'),
      USERPOINTS_EVAPORATE_WEEK => t('Week(s)'),
      USERPOINTS_EVAPORATE_MONTH => t('Month(s)'),
    ),
    '#default_value' => variable_get('userpoints_evaporate_inactive_unit', USERPOINTS_EVAPORATE_DAY),
  );
  return system_settings_form($form);
}

/**
 * Validation handler for the settings form.
 */
function userpoints_evaporate_admin_settings_validate($form, &$form_state) {
  if (!empty($form_state['values']['userpoints_evaporate_inactive_delta']) && intval($form_state['values']['userpoints_evaporate_inactive_delta']) < 1) {
    form_set_error('userpoints_evaporate_inactive_value][userpoints_evaporate_inactive_delta', t('Please enter a positive number'));
  }
}
