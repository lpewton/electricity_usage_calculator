const parameterOptions = document.getElementsByName('chosenParameter');

parameterOptions.forEach(option => {
  option.addEventListener('change', () => {
    if ($('#chosenParameterCheckbox1').prop('checked')) {
        $('#dayOrHourDiv').attr('class', '');
        $('#chosenDayDiv').attr('class', 'd-none');
        $('#chosen-period-div').attr('class', 'd-none');
    }
  });
});

parameterOptions.forEach(option => {
    option.addEventListener('change', () => {
      if ($('#chosenParameterCheckbox2').prop('checked')) {
          $('#chosenDayDiv').attr('class', '');
          $('#dayOrHourDiv').attr('class', 'd-none');
          $('#chosen-period-div').attr('class', 'd-none');
      }
    });
  });

  parameterOptions.forEach(option => {
    option.addEventListener('change', () => {
      if ($('#chosenParameterCheckbox3').prop('checked')) {
          $('#chosenDayDiv').attr('class', 'd-none');
          $('#dayOrHourDiv').attr('class', 'd-none');
          $('#chosen-period-div').attr('class', '');
      }
    });
  });