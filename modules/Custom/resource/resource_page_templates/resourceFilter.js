/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


(function ($) {
    $(document).ready(function() {
        
        $('#resource-ajax-filter').insertAfter($('#block-an-navigation-left-nav'));
        alert($('#content').html());
        $('#content').append($('#results-div'));
        
        $('.strategy-rollup').css('display', 'none');
        
        $('.stage-checkbox').click(function (e) {
            if (e.target.nodeName != 'LABEL') {
                $(this).next().toggle();
            }
        });
        
    });

}) (jQuery);