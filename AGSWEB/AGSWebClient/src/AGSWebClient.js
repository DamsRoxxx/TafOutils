// AGSWebClient.js

// Global variables
var _uiMainColor = "green";
var _apiURL = "http://" + location.hostname + ":8080"
var _nameFilter = "";
var _typeFilter = "Alarme";
var _dataFilter = "";
var _lastClickedName = "";
var _descobjet = null;

// Autorefresh displayed data
function RefreshCallback() {
  UpdateDisplayedData();
  setTimeout(RefreshCallback, 1000);
}
RefreshCallback();

// Main function
window.onload = function() {
  ManageDescObjet();
}

function ManageDescObjet() {
  AGSAPICall(_apiURL + "/descobjet", function(data) {
    // console.log(data);
    _descobjet = JSON.parse(data);
    var groupeSelect = document.getElementById("groupe-select");
    var espaceSelect = document.getElementById("espace-select");
    for (groupe in _descobjet) {
      var option = document.createElement("option");
      option.innerHTML = groupe;
      groupeSelect.appendChild(option);
      for (espace in _descobjet[groupe]) {
        var option = document.createElement("option");
        option.innerHTML = espace;
        espaceSelect.appendChild(option);
      }
    }
    groupeSelect.selectedIndex = 0;
    espaceSelect.selectedIndex = 0;
    FillNamesListV2();
    groupeSelect.onchange = function() {
      console.log("Rebuild espaces");
      var groupe = groupeSelect.options[groupeSelect.selectedIndex].innerHTML;
      var espaceSelect = document.getElementById("espace-select");
      espaceSelect.innerHTML = "";
      for (espace in _descobjet[groupe]) {
        var option = document.createElement("option");
        option.innerHTML = espace;
        espaceSelect.appendChild(option);
      }
      espaceSelect.selectedIndex = 0;
      FillNamesListV2();
    }
    espaceSelect.onchange = function() {
      FillNamesListV2();
    }
  });
}

function FillNamesListV2() {
  var namesListUl = document.getElementById("names-list-ul");
  var groupeSelect = document.getElementById("groupe-select");
  var espaceSelect = document.getElementById("espace-select");
  var groupe = groupeSelect.options[groupeSelect.selectedIndex].innerHTML;
  var espace = espaceSelect.options[espaceSelect.selectedIndex].innerHTML;
  namesListUl.innerHTML = "";
  if (_descobjet[groupe] == undefined) {
    console.log("Bad groupe");
    return;
  }
  if (_descobjet[groupe][espace] == undefined) {
    console.log("Bad espace");
    return;
  }
  console.log("GROUPE : " + groupe);
  console.log("ESPACE : " + espace);
  for (name in _descobjet[groupe][espace]) {
    var li = document.createElement("li");
    li.innerHTML = name;
    li.classList.add("w3-hover-" + _uiMainColor);
    li.onclick = function(event) {
      _nameFilter = _descobjet[groupe][espace][event.currentTarget.innerHTML]["nom"];
      UpdateDisplayedData();
      console.log(_nameFilter);
      if (_lastClickedName != "") {
        _lastClickedName.classList.remove("w3-green");
        event.currentTarget.classList.add("w3-green");
        _lastClickedName = event.currentTarget;
      } else {
        event.currentTarget.classList.add("w3-green");
        _lastClickedName = event.currentTarget;
      }
    }
    namesListUl.appendChild(li);
  }
}

// Fill the names-list-ul
function FillNamesList() {
  AGSAPICall(_apiURL + "/lightnameslist", function(data) {
    // Store the sorted names list in namesList
    var namesList = data.split(';').sort(function (a, b) {
      return a.toLowerCase().localeCompare(b.toLowerCase());
    });
    var namesListUl = document.getElementById("names-list-ul");

    // Fill the ul with li elements
    for (var i = 0; i < namesList.length; ++i) {
      var li = document.createElement("li");
      li.innerHTML = namesList[i];
      li.classList.add("w3-hover-" + _uiMainColor);
      li.onclick = function(event) {
        _nameFilter = event.currentTarget.innerHTML;
        UpdateDisplayedData();
        console.log(_nameFilter);
        if (_lastClickedName != "") {
          _lastClickedName.classList.remove("w3-green");
          event.currentTarget.classList.add("w3-green");
          _lastClickedName = event.currentTarget;
        } else {
          event.currentTarget.classList.add("w3-green");
          _lastClickedName = event.currentTarget;
        }
      }
      namesListUl.appendChild(li);
    }
  });
}

// Call the API url and execute ActionCallback on returned data
var actionDone = false;
function AGSAPICall(url, ActionCallback) {
  if (window.XMLHttpRequest) {
    xmlhttp=new XMLHttpRequest();
  }
  xmlhttp.onreadystatechange=function() {
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
      ActionCallback(xmlhttp.responseText);
    }
  }
  xmlhttp.open("GET", url, true);
  xmlhttp.send();    
}

function FillTable(name) {
  // Fill the dds-data-table
  // Head
  var table = document.getElementById("dds-data-table");
  table.innerHTML = "";
  var trHead = document.createElement("tr");
  for (var i = 0; i < 5; ++i) {
    var th = document.createElement("th");
    th.innerHTML = "COLUMN_" + String(i);
    trHead.appendChild(th);
  }
  table.appendChild(trHead);
  // Content
  var table = document.getElementById("dds-data-table");
  for (var i = 0; i < 100; ++i) {
    var tr = document.createElement("tr");
    for (var j = 0; j < 5; ++j) {
      var td = document.createElement("td");
      td.innerHTML = name + "_DATA_" + String(j);
      tr.appendChild(td);
    }
    table.appendChild(tr);
  }
}

function OpenTab(evt, type) {
  // Declare all variables
  var i, tabcontent, tablinks;

  _typeFilter = type;

  UpdateDisplayedData();

  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
  }

  evt.currentTarget.className += " active";
} 

function UpdateArrayV2(data) {
  // Parse JSON data
  var jdata = JSON.parse(data);

  // Clear current table content
  var table = document.getElementById("dds-data-table");
  table.innerHTML = "";

  // Return without doing nothing  if the _typeFilter is not something
  // displayable in a table
  if (_typeFilter == "" || _typeFilter == "All") {
    return;
  }

  // Describe columns order and label
  var alarmeColumnOrder = {
    "idInfo": "Code",
    "idCodePublic": "Code Public",
    "libelle": "Libelle",
    "active": "Active",
    "bagottante": "Bagottante",
    "inhibe": "Inhibe",
    "etatDepeche": "Dépêche",
    "gdhEmission": "Horaire"
  };
  var etatColumnOrder = {
    "idInfo": "Code",
    "idCodePublic": "Code Public",
    "libelle": "Libelle",
    "actif": "Active",
    "gdhEmission": "Horaire"
  };
  var infoGenColumnOrder = {
    "idInfo": "Code",
    "libelle": "Libelle",
    "idCodePublic": "Code Public",
    "param": "valeur",
    "gdhEmission": "Horaire"
  };
  var mesureColumnOrder = {
    "idInfo": "Code",
    "idCodePublic": "Code Public",
    "libelle": "Libelle",
    "valeur": "valeur",
    "gdhEmission": "Horaire"
  };
  var columnOrder = {
    "Alarme": alarmeColumnOrder,
    "Etat": etatColumnOrder,
    "InfoGen": infoGenColumnOrder,
    "Mesure": mesureColumnOrder
  }

  // Create table head
  var tr = document.createElement("tr");
  for (columnOrderKey in columnOrder[_typeFilter]) {
    var th = document.createElement("th")
    th.innerHTML = columnOrder[_typeFilter][columnOrderKey];
    tr.appendChild(th)
  }
  table.appendChild(tr);

  var sortedIdArray = CreateSortedIdArray(jdata, "idInfo");
  if (sortedIdArray == undefined) {
    return;
  }

  // Create table content
  for (var i = 0; i < sortedIdArray.length; ++i) {
    var dataId = String(sortedIdArray[i]["id"]);
    var tr = document.createElement("tr");

    // Change the date format of gdhEmission
    gdhEmission = new Date(parseInt(jdata[dataId]["gdhEmission"]) - new Date().getTimezoneOffset() * 60 * 1000);
    // jdata[dataId]["gdhEmission"] = gdhEmission.toISOString().replace(/[TZ]/g, " ").replace(/\..*/g, "");
    jdata[dataId]["gdhEmission"] = gdhEmission.toLocaleString('fr-FR', { timeZone: 'UTC' });
    for (columnOrderKey in columnOrder[_typeFilter]) {
      var td = document.createElement("td");
      td.innerHTML = jdata[dataId][columnOrderKey];

      // Color some boolean fields
      var booleanFieldsToColor = ["active", "actif"];
      if (booleanFieldsToColor.indexOf(columnOrderKey) > -1) {
        if (td.innerHTML == "true") {
          td.style.backgroundColor = "#4caf50"; // Green
        } else {
          td.style.backgroundColor = "#f44336"; // Red
        }
        td.innerHTML = "";
      }

      tr.appendChild(td);
    }
    table.appendChild(tr);
  }

  // SortTable("dds-data-table", 0)
}

function UpdateDisplayedData() {
  console.log("UpdateDisplayedData");
  AGSAPICall(_apiURL + "/data?name=" + _nameFilter +
             "&type=" + _typeFilter +
             "&filter=" + _dataFilter, function(data) {

    // If the type filter is not "All", output an array
    UpdateArrayV2(data);
  });
}

// Create a sorted ID like:
function CreateSortedIdArray(jdata, sortKey) {
  if (jdata[String(0)] == undefined) {
    return;
  }
  function DisplayArray(array, n) {
    var log = "ARRAY :\n";
    for (var i = 0; i < n; ++i) {
      log += '[' + String(i) + '] ' + array[i]["value"] + '\n';
    }
    console.log(log);
  }
  function InsertData(sortedIdArray, id, sortKeyValue) {
    var currentPos = id;
    while(currentPos >= 1 && sortedIdArray[currentPos - 1]["value"] > sortKeyValue) {
      sortedIdArray[currentPos]["id"] = sortedIdArray[currentPos - 1]["id"];
      sortedIdArray[currentPos]["value"] = sortedIdArray[currentPos - 1]["value"];
      --currentPos;
    }
    sortedIdArray[currentPos]["id"] = id;
    sortedIdArray[currentPos]["value"] = sortKeyValue;
  }

  var sortedIdArray = new Array(Object.keys(jdata).length);
  sortedIdArray[0] = {"id": 0, "value": jdata[String(0)][sortKey]};

  for (var i = 1; i < sortedIdArray.length; ++i) {
    // DisplayArray(sortedIdArray, i);
    // console.log("Insert data : " +jdata[String(i)][sortKey]);
    sortedIdArray[i] = {};
    InsertData(sortedIdArray, i, parseInt(jdata[String(i)][sortKey]));
  }
  // DisplayArray(sortedIdArray, sortedIdArray.length);
  return sortedIdArray;
}
