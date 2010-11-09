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
  return system_settings_form($form);
}
