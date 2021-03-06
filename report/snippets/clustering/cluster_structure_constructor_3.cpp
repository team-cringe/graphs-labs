pair<size_t, size_t> min = { -1, -1 };
for (auto& c1: ac) {
    for (auto& c2: ac) {
        if (c1.id() == c2.id()) { continue; }

        if (min.first > m_clusters.size()) {
            min = { c1.id(), c2.id() };
            continue;
        }

        if (m_dm_clusters(c1.id(), c2.id()) <
            m_dm_clusters(min.first, min.second)) {
            min = { c1.id(), c2.id() };
        }
    }
}