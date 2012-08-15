<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *Provides the navigation structure for the lifecycle section of the AN site.
 * @global type $GLOBALS['an_stage_strategy']
 * @name $an_stage_strategy 
 */
$GLOBALS['an_stage_strategy'] = array(
    'Developing a Trial' => array(
        'Stakeholder Enthusiasm' => 'Consider national and local stakeholder enthusiasm for the trial',
        'Recruitment Feasibility' => 'Evaluate the trial for recruitment feasibility',
        'Site Selection' => 'Choose Study Sites Carefully',
        'Trial Materials' => 'Prepare trial-specific materials',
        ),
    'Selecting & Preparing to Open a Trial' => array(
        'Portfolio and Participant Population' => 'Evaluate your institution’s clinical trial portfolio and participant population',
        'Infrastructure and Resources' => 'Assess your institution’s infrastructure and resources',
        'Stakeholder Commitment' => 'Ensure stakeholder commitment',
        'Participant Friendly Environment' => 'Create a participant friendly environment',
        'Internal Procedures' => 'Plan internal procedures to conduct the trial',
        'Recruitment and Retention Plan' => 'Write a comprehensive recruitment and retention plan',
        ),
    'Recruiting and Communicating with Participants' => array(
        'Engage Intermediaries' => 'Involve intermediaries to aid accrual',
        'Identify Participants' => 'Identify potentially eligible participants',
        'Informed Consent' => 'Engage participants in the Informed Consent Process',
        'Participant Financial Issues ' => 'Consider participant financial issues',
        'Maintain Morale and Interest' => 'Maintain the morale and interest of staff, participants and their families',
        'Update Participants' => 'Update participants regarding study related events and results',
        ),
    'Implementing the Trial' => array(
        'Communicate with Stakeholders' => 'Communicate regularly with stakeholders and referring providers',
        'Progress and Metrics' => 'Monitor trial progress and accrual metrics',
        'Alternative Recruitment Strategies' => 'Implement alternative recruitment strategies when accrual milestones are not achieved',
        ),
    'Evaluating Accrual and Reporting Lessons Learned' => array(
        'Lessons Learned' => 'Analyze the trial’s accrual data for lessons learned',
        'Report and Share' => 'Report and share accrual experiences with others',
        ),
    );


function _an_lifecycle_create_nodes () {
    global $an_stage_strategy;
   
    foreach ($an_stage_strategy as $stage => $strategies) {
        $stratIDs = array();
        foreach ($strategies as $stratShort => $stratLong) {
            $nodeStrat = new stdClass();
            $nodeStrat->type = 'lifecycle_strategy';
            node_object_prepare($nodeStrat);
            
            $nodeStrat->language = LANGUAGE_NONE;
            $nodeStrat->status = 1;
            $nodeStrat->comment = 1;
            
            $nodeStrat->title = $stratLong;
            $nodeStrat->field_nav_label[$nodeStrat->language][]['value'] = $stratShort;
            $nodeStrat->created = time();
            $nodeStrat->changed = time();
            
            $nodeStrat->field_content_summary[$nodeStrat->language][]['value'] = $stratLong;
            
            node_save($nodeStrat);
           $stratIDs[] = $nodeStrat->nid;
        }
        $nodeStage = new stdClass();
        $nodeStage->type = 'lifecycle_stage';
        node_object_prepare($nodeStage);
        
        $nodeStage->language = LANGUAGE_NONE;
        $nodeStage->status = 1;
        $nodeStage->comment = 1;
        
        $nodeStage->title = $stage;
        $nodeStage->created = time();
        $nodeStage->changed = time();
        
        foreach ($stratIDs as $stratID) {
        $nodeStage->field_child_strategies[$nodeStage->language][]['target_id'] = $stratID;
        }
        node_save($nodeStage);
    }
}

?>
