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


/*function($) {
	var size = $('input').size();
	alert ("Matched " + size + " elements.");
	//.change(function() {alert('Handler for .change() called.');});
}(jQuery);*/
