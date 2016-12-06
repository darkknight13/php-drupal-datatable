<?php 

Class DrupalDataTable{
    private $headers = array();
    private $attributes = array();
    private $rows = array();
    private $variables = array();
    private $build = array();

    public function __construct() {}

    public function attributes($features) {
        foreach ($features as $attrKey => $value) {
            $this->addAttribute($attrKey, $value);
        }
        return $this;
    }

    public function attribute($attrKey, $value) {
        $this->addAttribute($attrKey, $value);
        return $this;
    }

    protected function addAttribute($attrKey, $value) {
        $OptionList = $this->getOptionList();
        $conditionMet = false;
        if (isset($OptionList[$attrKey]) && is_array($OptionList[$attrKey])) {
            foreach ($OptionList[$attrKey] as $requiredItems) {
                if (isset($this->attributes[$requiredItems]) || isset($features[$requiredItems])) {
                    $conditionMet = true;
                }
            }
        } else if (in_array($attrKey, $OptionList)) {
            $conditionMet = true;
        }
        if ($conditionMet) {
            $this->attributes[$attrKey] = $value;
        }
    }

    public function header($title, $type = 'string', $sortable = true, $searchable = true, $width = '10') {
        $this->headers[] = array(
            'data' => t($title),
            'datatable_options' => array(
                'sTitle' => $title,
                'sType' => $type,
                'bSortable' => $sortable,
                'bSearchable' => $searchable,
                'sWidth' => $width . '%'
            )
        );
        return $this;
    }

    public function data($rows = array()) {
        $this->rows = $rows;
        return $this;
    }

    public function theme() {
        $this->variables = array(
            'attributes' => array(
                'datatable_options' => $this->attributes
            ),
            'header' => $this->headers,
            'rows' => array()
        );
        return $this;
    }

    public function render() {
        $this->build =  array(
            '#theme' => 'datatable',
            '#attributes' => array(
                'datatable_options' => $this->attributes
            ),
            '#header' => $this->headers,
            '#rows' => array()
        );
        return $this;
    }

    public function output($type='theme'){
        if($type = 'render'){
            if(empty($this->build)){
                $this->render();
            }
            return render($this->build);
        } else {
            if(empty($this->variables)){
                $this->theme();
            }
            return theme('datatable', $this->variables);
        }
    }

    protected function getOptionList() {
        $OptionList = array(
            'bAutoWidth',
            'bDeferRender',
            'bFilter',
            'bInfo',
            'bJQueryUI',
            'bLengthChange',
            'bPaginate',
            'bProcessing',
            'scrollX',
            'scrollY',
            'bServerSide' => array(
                'bServerSide',
                'sAjaxSource'
            ),
            'bSort',
            'bSortClasses',
            'bStateSave',
            'sScrollX',
            'sScrollY',
            'sAjaxSource',
            'fnDrawCallback'
        );
        return $OptionList;
    }
}
