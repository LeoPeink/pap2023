#pragma once

//file per mantenere in modo ordinato i diversi messaggi di errore che potrebbero presentarsi durante l'uso dell'interfaccia.

const std::string E_VERTEX_ALREADY_EXISTING	{ "ERROR: SPECIFIED VERTEX ALREADY EXISTING.\n" };
const std::string E_MISSING_VERTEX			{ "ERROR: SPECIFIED VERTEX NOT FOUND.\n" };
const std::string E_NEGATIVE_WEIGHT_CYCLE	{ "WARNING: NEGATIVE CYCLE DETECTED. SOLUTION MAY NOT BE OPTIMAL.\n" };
const std::string E_MISSING_EDGE			{ "ERROR: SPECIFIED EDGE NOT FOUND.\n" };
const std::string E_EMPTY_GRAPH				{ "ERROR: ALGORITHM CALLED ON EMPTY GRAPH.\n"};
const std::string E_NEGATIVE_GRAPH			{ "WARNING: NEGATIVE WEIGHT DETECTED. SOLUTION MAY NOT BE OPTIMAL.\n." };
