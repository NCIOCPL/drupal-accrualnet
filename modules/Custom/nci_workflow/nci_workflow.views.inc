<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function nci_workflow_views_query_alter(&$view, &$query) {
	if ($view->name == 'an_workflow') {

		// search through the query for the values to tweak
		switch ($view->current_display) {
			case 'block_writer_inbox':
				$fragment = 'writer';
				break;
			case 'block_editor_inbox':
				$fragment = 'editor';
				break;
			default:
				return;
		}
		$table = "field_revision_field_assigned_$fragment";
		$field = "field_assigned_${fragment}_value";

		// look for the target assign field that matches non-null...
		// this is our hook to alter with the current user id
		foreach ($query->where as $where_ix => $element) {
			foreach ($element['conditions'] as $cond_ix => $condition) {
				if ($condition['field'] == "$table.$field" &&
						$condition['operator'] == "IS NOT NULL") {

					// set this condition to look for the current user
					global $user;

					$query->where[$where_ix]['conditions'][$cond_ix]['value'] =
							check_plain($user->uid);
					$query->where[$where_ix]['conditions'][$cond_ix]['operator'] =
							'=';
				}
			}
		}
	}
}

?>
