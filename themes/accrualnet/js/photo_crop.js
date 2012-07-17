/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

jQuery(document).ready(function($) {
	$('#edit-picture-upload').val("");//.hide();
	$('#edit-picture-upload').change(function() {
		alert("Browsed for url " + $(this).val());
	});
});
