/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */




(function ($) {
    $(document).ready(function() {
        



        
        $('#resource-ajax-filter').insertAfter($('#block-an-navigation-left-nav'));
        
        

        $('#content').append($('#results-div'));
        
        $('ul.pager').addClass('literature-pager');
        $('li.pager-ellipsis').css('display', 'none');
        $('li.pager-last').css('display', 'none');
        $('#title-results-pager').append($('ul.pager').clone());
        
        $('.strategy-rollup').css('display', 'none');
        
        $('.stage-checkbox').click(function (e) {
            if (e.target.nodeName != 'LABEL') {
                $(this).next().toggle();
            }
        });
        
        // Reset the filter by just reloading the base page
        var $resetFilter = $('form#resource-ajax-filter').attr('action');
        $('#filter-results').append($('<div class="reset-filter"><a href="' + $resetFilter + '">Reset Filter</a></div>'));
    
    
        $('<span class="filter-arrow collapsed">► </span>').insertBefore($('#edit-lifecycle, #edit-resource-types').children('legend').children('span'));
        $('#edit-lifecycle, #edit-resource-types').children('legend').next().css('display', 'none');
        $($('#edit-lifecycle, #edit-resource-types').children('legend')).click(function () {
            $(this).next().toggle();
            if ($(this).children('.filter-arrow').hasClass('collapsed')) {
                $(this).children('.filter-arrow').html("▼ ");
                $(this).children('.filter-arrow').removeClass('collapsed');
                $(this).children('.filter-arrow').addClass('expanded');
            } else if ($(this).children('.filter-arrow').hasClass('expanded')) {
                $(this).children('.filter-arrow').html("► ");
                $(this).children('.filter-arrow').addClass('collapsed');
                $(this).children('.filter-arrow').removeClass('expanded');
            }
        });

    });

}) (jQuery);