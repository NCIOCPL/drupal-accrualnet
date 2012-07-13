/*
 * Added By: Lauren
 * Added On: July 13, 2012
 * 
 * Last Modified By: Lauren
 * Last Modified On: July 13, 2012
 * 
 * Based on script from:
 * http://www.maratz.com/blog/archives/2006/06/11/fancy-checkboxes-and-radio-buttons/
 */

(function ($) {

    $(document).ready(function(){
        var test = '.form-type' + '-checkbox';
          /*$(test).addClass('supatest'); works */
jQuery.each($('.form-type-checkbox'), function() {
    var $clslst = new String($(this)[0].classList);
    var $found = false;
    for (key in Drupal.settings.myvarname) {
        
    
    if ($clslst.indexOf(Drupal.settings.myvarname[key]) > -1) {
        
    $found = true;
   /*$(this).find('label').addClass('checked');*/
   $(this).addClass('checked');
  break;
    }
    }
    if (!$found) {
        /*$(this).find('label').addClass('unchecked');*/
        $(this).addClass('unchecked');
    }
    
    
    /*alert($(this)[0].classList);
    alert($(this).is(':checked'));*/
   
    
});
  var testy = '.form-item-field-role-und-select-' + Drupal.settings.myvarname[0];
          alert(testy);
          /*$(testy).addClass('supatest');*/
          $('.form-item-field-role-und-select-Administration/Management').addClass('supatest');
        for(key in Drupal.settings.myvarname) {
           /* alert(key); works */
           /*$('field_role[und][select]['.key.']').addClass('supatest');*/
          /* $('.form-item-field-role-und-select-' + (string) key).addClass('supatest');*/
          var test2 = 'form-item-field-role-und-select-' + Drupal.settings.myvarname[key];
       /*   alert(test2);
          $(test2).addClass('supatest');*/
        }
        var $j = jQuery.noConflict();
        $('.form-type-checkbox').attr('checked', true);
        
        $('.form-type-checkbox').click(function () {
            $(this).removeClass('supatest');
        });

    
  });
})(jQuery); 

var d = document;
var safari = (navigator.userAgent.toLowerCase().indexOf('safari') != -1) ? true : false;
var gebtn = function(parEl,child) {return parEl.getElementsByTagName(child);};
onload = function() {
    var form = document.getElementById('user-profile-form');

    var body = gebtn(d,'body')[0];
    body.className = body.className && body.className != '' ? body.className + ' has-js' : 'has-js';
    
    if (!d.getElementById || !d.createTextNode) return;
    var ls = gebtn(d,'label');

    for (var i = 0; i < ls.length; i++) {
        var l = ls[i];
        if (l.className.indexOf('form-item') == -1) continue;
        var inp = gebtn(l,'input')[0];
        if (l.className == 'label_check') {
            l.className = (safari && inp.checked == true || inp.checked) ? 'label_check c_on' : 'label_check c_off';
            l.onclick = check_it;
        };
        /*if (l.className == 'label_radio') {
            l.className = (safari && inp.checked == true || inp.checked) ? 'label_radio r_on' : 'label_radio r_off';
            l.onclick = turn_radio;
        };*/
    };
};
var check_it = function() {
    var inp = gebtn(this,'input')[0];
    if (this.className == 'label_check c_off' || (!safari && inp.checked)) {
        this.className = 'label_check c_on';
        if (safari) inp.click();
    } else {
        this.className = 'label_check c_off';
        if (safari) inp.click();
    };
};
/*var turn_radio = function() {
    var inp = gebtn(this,'input')[0];
    if (this.className == 'label_radio r_off' || inp.checked) {
        var ls = gebtn(this.parentNode,'label');
        for (var i = 0; i < ls.length; i++) {
            var l = ls[i];
            if (l.className.indexOf('label_radio') == -1)  continue;
            l.className = 'label_radio r_off';
        };
        this.className = 'label_radio r_on';
        if (safari) inp.click();
    } else {
        this.className = 'label_radio r_off';
        if (safari) inp.click();
    };
};*/

