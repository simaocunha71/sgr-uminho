package model.interfacesSGR;

import java.io.Serializable;

/**
 * Interface para a SGR
 */
public interface SGR extends ReadingSGR, StatisticsSGR, UsersCatalog, ReviewsCatalog,
        BusinessesCatalog, Queries, Serializable {
}
